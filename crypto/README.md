# Akasec-CTF-2024 Crypto

## [Lost](https://github.com/sou200/Akasec-CTF-2024/tree/master/Lost)
Do you know the feeling of losing a part of you !!

**source:**

    from random import getrandbits
    from Crypto.Util.number import getPrime, bytes_to_long
    
    from SECRET import FLAG
    e =  2
    p = getPrime(256)
    q = getPrime(256)
    n = p * q

    m = bytes_to_long(FLAG)
    cor_m = m - getrandbits(160)
    
    if  __name__  ==  "__main__":
    c =  pow(m, e, n)
    print("n = {}\nc = {}\ncor_m = {}".format(n, c, cor_m))
if we print `cor_m` it well give us a portion of the flag :

> b'AKASEC{c0pp3r5m17h_4774ck_1n_1ov3_v\xc0gx\xff\x1d-\x10u\xf8\xee\xe4J\x0c\x96\x11\x9d\xfb2'

 so if we want to recover the flag we have to use `Coppersmith's attack`
 which is implemented in `sagemath` as you can see.
 
 **solve:**

    n = 5113166966960118603250666870544315753374750136060769465485822149528706374700934720443689630473991177661169179462100732951725871457633686010946951736764639
    c = 329402637167950119278220170950190680807120980712143610290182242567212843996710001488280098771626903975534140478814872389359418514658167263670496584963653
    cor_m = 724154397787031699242933363312913323086319394176220093419616667612889538090840511507392245976984201647543870740055095781645802588721
    e = 2
    P.<x> = Zmod(n)[]
    
    f = (cor_m + x)^e - c
    
    r = f.small_roots()[0]
    
    from Crypto.Util.number import *
    
    print(r)
    print(long_to_bytes(Integer(cor_m + r)))

## [Power over all](https://github.com/sou200/Akasec-CTF-2024/tree/master/Power%20over%20all)
Power is given only to those who dare to lower themselves and pick it up. Only one thing matters, one thing, to be able to dare!

**source:**

    from Crypto.Util.number import getPrime, bytes_to_long
    from random import randint
    from SECRET import FLAG
    
    def  key_gen():
    ps = []
    n = randint(2,2**6)
    for _ in  range(n):
	    p = getPrime(256)
	    ps.append(p)
	    return ps
    
    def  encrypt(m, ps):
	    ps.sort()
	    for p in ps:
		    e =  1<<1
		    m =  pow(m, e, p)
	    return m
    
    if  __name__  ==  "__main__":
	    ps = key_gen()
	    c = encrypt(bytes_to_long(FLAG), ps)
	    print('ps = {}\nc = {}'.format(ps, c))

this a simple `quadratic residue` challenge, if we calculate `p[i] % 4` it will give us `1` or `3` so we have to use `Tonelli-Shanks` algorithm.

**solve:**

    from Crypto.Util.number import long_to_bytes
    
    ps = [58320376514263631335873677765253125888698486914776244278840394907785982174227, 58471100903556849464997941473361218814224259836954194397969653104598610032001, 58604272362819290182402155417145974680722885151257754555756391392263925028373, 59492683945798085501800206338526899942899780311409115479365237372756535853291, 62289703300031234585435188246756616897767167359387015636210423567810538226487, 62357776874227535169229603723986677552237575016029450363623522209118965731477, 62742816090727067053274726868556821524033631101402012261515152539681610794161, 63324484395885397762900693586081837883926106660748610230948918800296364184787, 68536318595052838310834810610435117143127088803068602445335475326427140828313, 71333662629967127822322169475282958517332768085026414016527475771426692311137, 71818789628596987832122424763592924131858666988566206124807910367000034628553, 72686903390659724206544737536831534683324964478965218565533472954938736006029, 73733187867854099083339033682720615801689502367745526033697746193463091215391, 74963435458999407861524268290816092282448161750409920047891056819453141955557, 75170120333127044486222669300167892338904422362667312672451826995740967131303, 75389546402724552962462061186170732933053151602764277596760332277139980288183, 76425604829327821607866318415668087016313389323090875428602763671306466213509, 79395489525333852455993920714320320052245084253382013156160044439065839468327, 79656464249999345933529538948250990091001499735972420522175125449790253663599, 80114644787477907454032975169773036722948929091396695518111556258640245353257, 80759006745106776887940527633196344281100618167707846074299752297932178679679, 82874221581479658193940394796733443765246468888210669340444752189895488345711, 84468817045619298841099296118053247701538652785316191917289525698631379587559, 85092225008500173289712181614303627906592443829912221851650912999596788670459, 85263141959763159396039844302970550543465193325499728803392808980592668472247, 85317220893586781914729151221061742320435924332561513947650447739620101821641, 85440269113801669657707134806659364077593365787015642755204798072592063745773, 85527879261087022928016922730880335213911499029647505445360684307006839178647, 85605932852710450456174796386471227136632343649286364769039469217779231567929, 86107819754589869545139506654865763056227887269808133233781131410193748463851, 86163843486640208219217644606617383296879865315755352427047957187159788303323, 90506049416840638351240993555664643907544570698557428055802715993870286417397, 90981593208992230235747480738729958015954461329514397574562251177250355618859, 94292491231252601103954494535972386523808989201770556967497120902651386194197, 94647786177270050686880223709072304737527824812798720504615370320158513996239, 95245024143291248356010627064844329722889005501412707859257139919568967846749, 96080930363425942206733690433078387012542225534990227081492087888246704507441, 97503025379673346416669602471064834261095444529417927406127397664552811080519, 97933089652660434994459543027801105444314465759238615625507952727940600189809, 97989967696425430412414365007330195727579540568089381507635553281304266294483, 98528881400840757343372680020873216862352604380253902505512625033610753437887, 99954243543097817759175467071884308315066389399425962144138323810271659014209, 101194437697606745792831239895049471075868629243259633705095039109106669730049, 104839585136982979038455371159792466832240349600316352323298553695087849421381, 105456177698115744366058226841117004148984862640508652026693415913601327156663, 105968680258458596148231537242426487615777154901757802179920828015643162453013, 107215231310505428676141499322854084705449980120508349014281658724461432400217, 108453510226000323101878638579711809016925129461454736081626840494612032349563, 108912309872075893365304953396355888979232521108447384367848671194555817947569, 108997022694208058790012872910875462503431062529475661062287324154956518493253, 109322568022936420513907683387388159609608845110397725890561824119551381299491, 110029910646386857435917200277309270534213159892118369614262345955187628998231, 113144116692201726589659464242284454643667198002480615110504233499994524508369, 114364819674774846158222033218389865879337160752260853195966728903452922982539, 115473149458023487534963694928189868221104180303262395583076896364124371580681]
    c = 53630975642867707857977893429296334474716191527562307357222551886495223105860
    def legendre(a, p):
        return pow(a, (p - 1)//2, p)
    
    def tonelli_shanks(n, p):
        assert p > 2
        assert legendre(n, p) == 1
    
        q = p - 1
        s = 0
        while q % 2 == 0:
            q //= 2
            s += 1
    
        z = 2
        while pow(z, (p - 1) // 2, p) == 1:
            z += 1
    
        m = s
        c = pow(z, q, p)
        t = pow(n, q, p)
        r = pow(n, (q + 1) // 2, p)
    
        while t != 1:
            t2i = t
            i = 0
            for i in range(1, m):
                t2i = pow(t2i, 2, p)
                if t2i == 1:
                    break
            b = pow(c, 2**(m - i - 1), p)
            m = i
            c = pow(b, 2, p)
            t = (t * c) % p
            r = (r * b) % p
    
        return r
    
    solves1 = [c]
    
    for p in reversed(ps):
        solves = [k for k in solves1 if legendre(k, p) == 1]
        solves1 = []
        for s in solves:
            a = tonelli_shanks(s, p)
            solves1.append(a)
            solves1.append(-a%p)
    
    for c in solves1:
        m = long_to_bytes(c)
        if b'AKASEC' in m:
            print(m)

## [GCL](https://github.com/sou200/Akasec-CTF-2024/tree/master/GCL)
all about THEORIC and some LUCK.

***source***

    from random import getrandbits
    from Crypto.Util.number import getPrime
    from SECRET import FLAG
    
    BITS = 128
    m = getPrime(BITS)
    s = getrandbits(BITS - 1)
    a = getrandbits(BITS - 1)
    b = getrandbits(BITS - 1)
    
    def lcg(s, c):
        return c*(a*s + b) % m
    
    if __name__ == "__main__":
        c = []
        r = s
        for i in FLAG:
            r = lcg(r, ord(i))
            c.append(r)
        print("m = {}\nc = {}".format(m, c))
this is a simple `modular arithmitic` problem.
we have to find `a`, `b`, (`s`, optional)  so we just have to do some math operation between those equations to find `roots`:

> c1 = f1 * (a * s + b) % m
> 
> c2 = f2 * (a * c1 + b) % m
> 
> c3 = f2 * (a * c2 + b) % m
> 
> ..

> f1 = ascii of 'A'
> 
> f2 = ascii of 'K'
> 
> f3 = ascii of 'A'

**solve**

    m = 188386979036435484879965008114174264991
    c = [139973581469094519216727575374900351861, 72611500524424820710132508411012420565, 140250284171774823110472025667980956543, 32777758636601391326104783245836052689, 93866424818360655182957373584240082579, 171863599957625964609271128026424910780, 79519361871833866309751703823833758895, 157560014678333843523667019607330519198, 124975940725420603096426178838171348774, 3564693226938115115868719960412136082, 171740395033004244209129576880703758137, 92351702560499873288607191820522016910, 150094682983991168941275074808189562445, 85216665671310516224623100332845098274, 16595528649897543867800038656511154165, 19125026372283368463438507438570762609, 176795229245184227193627490600890111381, 12405536363393343486876802251851443164, 21411546298976790262184367895329536928, 182888536880153351183725282563493758721, 138117470020493616013148815568927291737, 32287599436436170232396368906599005001, 163785640221676961026807618948041121515, 73960913430365454320029097511676942987, 15454719718422589834477927328058381231, 187548967342452768771256903662911504220, 159561161576243464490176365717896800999, 68751190791869748062871941359673493536, 121231243784105483671509398006895458898, 14881767206744163076100305953646446453, 175267890044871169868897060667629218625, 147751087332703693307658387948934053643, 144192171120888146499506968416035431150]
    a = (c[1]*pow(ord("K"), -1, m) - c[2]*pow(ord("A"), -1, m))*pow(c[0] - c[1], -1, m) % m 
    b = (c[1]*pow(ord("K"), -1, m) - a * c[0]) % m
    s = (c[0]*pow(ord("A"), -1, m) - b)*pow(a, -1, m) % m
    
    def mylcg(s):
        return a*s + b % m
    
    flag = ""
    
    s = mylcg(s)
    for i in c:
        v = pow(s, -1, m)*i % m
        flag += chr(v)
        s = mylcg(i)
    
    print(flag)

## [Twin](https://github.com/sou200/Akasec-CTF-2024/tree/master/Twin)
I have a twin but he doesn't looks like me !!, so sad isn't !?

**source:**

    from Crypto.Util.number import getPrime, bytes_to_long
    from SECRET import FLAG
    
    e = 5
    p = getPrime(256)
    q = getPrime(256)
    n = p * q
    
    m1 = bytes_to_long(FLAG)
    m2 = m1 >> 8
    
    if __name__ == "__main__":
        c1, c2 = pow(m1, e, n), pow(m2, e, n)
        print("n = {}\nc1 = {}\nc2 = {}".format(n, c1, c2))

we have `c1` and `c2` which is encryption of `m1` and `m2`.
`m2` is `m1` shifted right by (`8-bit` = `1-byte` = `1-character`) that `1-character` is `}` last character in the flag.
so `m1 = 2^8 * m2 + ascii_of('}') = 256 * m2 + ord('}')`
then:

> c1 = (256 * *m2* + ord('}'))^e % n
> 
> c2 = (*m2*)^e % n
 
 now we have `m2` in both equations so we can you use `franklin-reiter related message attack`.
 
**solve:**

    from Crypto.Util.number import *
    
    n = 6689395968128828819066313568755352659933786163958960509093076953387786003094796620023245908431378798689402141767913187865481890531897380982752646248371131
    c1 = 3179086897466915481381271626207192941491642866779832228649829433228467288272857233211003674026630320370606056763863577418383068472502537763155844909495261
    c2 = 6092690907728422411002652306266695413630015459295863614266882891010434275671526748292477694364341702119123311030726985363936486558916833174742155473021704
    
    e = 5
    R.<X> = Zmod(n)[]
    f1 = (256*X + ord('}'))^e - c1
    f2 = X^e - c2
    
    def my_gcd(a, b): 
        return a.monic() if b == 0 else my_gcd(b, a % b)
    
    m2 = my_gcd(f1, f2).small_roots()[0]
    m1 = (m2 << 8) + ord('}')
    
    print(long_to_bytes(Integer(m1)))
