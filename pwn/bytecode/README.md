# Bytecode

I made a bytecode interpreter without reading books. Isn't programming about feeling it?

```
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

## Writeup
Is this challenge a bit overkill? Maybe. 

The challenge is to find a way to exploit a shitty bytecode interpreter using classic FSOP technique paired with other small bugs.
The instructions provided are basic, such as add, sub, xor, pop, and push.

You are given a page of memory addressable via mmap and a temporary stack in the BSS section. The first step to exploit the challenge is to leak an address in libc. The `PUTS` instruction dereferences and prints an address from the BSS:
```c
case PUTS: // puts only accepts addresses from bss
    i++;
    if ((unpack(code + i, sizeof(int)) & 0xffffff00) ==
            ((uint64_t)(stack) & 0xffffff00) &&
            (unpack(code + i, sizeof(int)) < (stack + STACK_SIZE))) {
        puts((char *) unpack(code + i, sizeof(int)));
    }
    i += 4;
    break;
```

The `if` statement checks if the printed address is within the first 255 bytes of the BSS. 
Just before our fake stack, we can find the addresses of libc stdin and stdout, which we can print to get a libc leak.

Writing in the BSS isn't enough to inject our payload. We can also see another variable in the BSS from the stack, which we can print by pushing strings of 8 characters into the fake stack until it is full.
This overwrites the last null byte in the fake stack and leaks a stack address by printing the full string.

Now that we have leaks, remember the stdin and stdout pointers? We can write to those memory addresses and craft our own fake FILE structures in the bss to overwrite the return pointer in the stack. It’s a bit messy but will get the job done.