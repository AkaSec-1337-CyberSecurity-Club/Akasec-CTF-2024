const express = require('express');
const multer = require('multer');
const bcrypt = require('bcrypt');
const randomstring = require('randomstring');
const session = require('express-session');
const path = require('path');
const Datastore = require('nedb');
const ejs = require('ejs');
const flash = require('connect-flash');
const PDFJS = require('pdfjs-dist');
const bot = require("./bot")
const rateLimit = require("express-rate-limit")

const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
const secretKey = randomstring.generate(32);

app.use(session({
  secret: secretKey,
  resave: false,
  saveUninitialized: false,
  cookie: { name: 'sid' }
}));

app.use(flash());
app.set('views', path.join(__dirname, 'views'));
app.use('/img', express.static(path.join(__dirname, 'img')));
app.set('view engine', 'ejs');
app.set('trust proxy', true);

const limit = rateLimit({
    ...bot,
    validate: {
	validationsConfig: false,
	default: true,
    },
    handler: ((req, res, _next) => {
        const timeRemaining = Math.ceil((req.rateLimit.resetTime - Date.now()) / 1000)
        res.status(429).json({
            error: `Too many requests, please try again later after ${timeRemaining} seconds.`,
        });
    })
})

const users = new Datastore({ filename: path.join(__dirname, 'users.db'), autoload: true });
const uploadfile = new Datastore({ filename: path.join(__dirname, 'uploadfile.db'), autoload: true });

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    cb(null, './uploads');
  },
  filename: (req, file, cb) => {
    cb(null, file.fieldname + '-' + Date.now() + path.extname(file.originalname));
  },
});

const upload = multer({ 
  storage: storage,
  fileFilter: (req, file, cb) => {
    if (file.mimetype == "application/pdf") {
      cb(null, true);
    } else {
      cb(null, false);
      return cb(new Error('Only .pdf format allowed!'));
    }
  }
});

app.get('/', (req, res) => {
  res.render('index');
});

app.get('/signup', (req, res) => {
  res.render('signup');
});

app.post('/signup', async (req, res) => {
	users.findOne({ username: req.body.username }, async (err, user) => {
	  if (user) {
		res.status(400).send('Username already exists');
	  } else {
		const hashedPassword = await bcrypt.hash(req.body.password, 10);
		users.insert({ username: req.body.username, password: hashedPassword }, (err, newUser) => {
		  if (err) {
			res.status(500).send('Error creating user');
		  } else {
			res.redirect('/login');
		  }
		});
	  }
	});
});

app.get('/login', (req, res) => {
  res.render('login');
});

app.post('/login', async (req, res) => {
	users.findOne({ username: req.body.username }, async (err, user) => {
	  if (err) {
		res.status(500).send('Error logging in');
	  } else if (user && await bcrypt.compare(req.body.password, user.password)) {
		req.session.user = req.body.username;
		res.redirect('/upload');
	  } else {
		res.send('Invalid username or password');
	  }
	});
});

app.get('/upload', (req, res) => {
	let error = req.session.error;
	if (error) {
	  req.flash('error', 'Your error message');
	  return res.redirect('/upload');
	}	
	if (req.session.user) {
	  res.render('upload');
	} else {
	  res.redirect('/login');
	}
});

app.post('/upload', upload.single('file'), (req, res) => {
	const fileData = {
	  filename: req.file.filename,
	  path: req.file.path,
	  user: req.user
	};
  
	uploadfile.insert(fileData, (err, newDoc) => {
	  if (err) {
		res.status(500).send(err);
	  } else {
		res.redirect('/view/' + req.file.filename);
	  }
	});
});

app.get('/logout', (req, res) => {
  req.session.destroy(err => {
    if(err) {
      return res.redirect('/upload');
    }
    res.clearCookie('connect.sid');
    res.redirect('/login');
  })
});

app.use('/uploads', express.static(path.join(__dirname, 'uploads')));
app.use('/pdf.js', express.static(path.join(__dirname, 'node_modules/pdfjs-dist/build/pdf.js')));
app.use('/pdf.worker.js', express.static(path.join(__dirname, 'node_modules/pdfjs-dist/build/pdf.worker.js')));

app.get('/view/:filename', async (req, res) => {
    let filename = req.params.filename;
    res.render('view', { filename: filename });
});

app.get("/report", (_, res) => {
    const { name } = bot
    res.render("bot", { name });
});

app.post("/report", limit, async (req, res) => {
    const { url } = req.body;
    if (!url) {
        return res.status(400).send({ error: "Url is missing." });
    }
    if (!RegExp(bot.urlRegex).test(url)) {
        return res.status(422).send({ error: "URL din't match this regex format " + bot.urlRegex })
    }
    if (await bot.bot(url)) {
        return res.send({ success: "Admin successfully visited the URL." });
    } else {
        return res.status(500).send({ error: "Admin failed to visit the URL." });
    }
});

app.get('/flag', (req, res) => {
  let ip = req.connection.remoteAddress;
  if (ip === '127.0.0.1') {
    res.json({ flag: 'AKASEC{PDF_1s_4w3s0m3_W1th_XSS_&&_Fr33_P4le5T1n3}' });
  } else {
    res.status(403).json({ error: 'Access denied' });
  }
});

app.listen(5000, '0.0.0.0', () => console.log('Server started on port 5000'));
