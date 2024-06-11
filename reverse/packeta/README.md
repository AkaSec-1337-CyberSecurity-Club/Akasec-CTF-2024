# packeta
 - packeta is a small half packer, that encrypt .text .data and .rodata sections of the elf64 binaries.
 - The encryption process is based upon creating a range of encryption keys (500 key), and chosing one randomly to encrypt the sections using RC4.
 - the intended solution is basically to recover the elf, by producing all the keys in the seed range, and bruteforcing decryption until a valid key that makes the binary execute without erorrs.
 - solve.c has a solution written in C.
 - the unintended solution is to make a script that execute `./packeta flag` until It runs properly.One way to make it hard, is by increasing the key range (50000++).

 