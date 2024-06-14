# good_trip

## Description
If you think about it, it doesn't make any sense. GOOOOD TRIP.

## Writeup
```
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```
We have a basic binary that mmaps a region of memory with read, write, and execute permissions. The program then asks the user for a code size, reads up to 0x1000 characters as the code size, applies `mprotect` to the memory region, runs the code through a filter that disallows 'syscall', 'int 0x80', and 'sysenter' opcodes, and finally executes the code.

The vulnerability is quite obvious. The program asks for a code size, but reads up to 0x999 characters regardless, which could raise suspicion.

If `mprotect` is given a code size less than 1, it fails. There is no protection to abort the program, so the memory region retains its default permissions, meaning we can still write to it after passing the check.

To exploit the program, you just need to set the registers, push the syscall opcode into the memory, and then jump to it.