# Warmup 

## Description 

Here's something to get you warmed up. Spin that `gdb` up!

## Writeup

**Checksec Output:**
```
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)
```

This is a very simple challenge, a warmup.

The challenge prints a leak from `libc` then takes two inputs: `name` and `flow`.

- **name** [0x200] is stored in the `.bss` section.
- **flow** [64] is stored on the stack.

We can see that the `flow` input is greater than 64 bytes, which means we can control the `RIP`, but our space would be very limited.

This challenge can be solved in two ways:

### One Gadget

The `libc` is provided in the docker, so we can simply take a one gadget and inject it.

### Stack Pivoting

We can also stack pivot and call gadgets from `libc` since we do have a leak. 
This can be achieved by injecting the ROP payload into the `name` buffer and modifying the saved `RBP` to return to the payload in the `.bss` section.