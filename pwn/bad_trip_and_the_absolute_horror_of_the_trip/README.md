# Bad Trip

I'm giving you a leak; how can't you solve this? BAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD TRIP.

# The Absolute Horror of the Trip

Think you can handle a bad trip? Ever thought about taking a heroic dose?

```
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled
```

## Writeup
These challenges were an absolute failure due to the lack of proper challenge engineering. I admit, I spent way too much time working on making the challenge exploitable while ignoring unintended solutions and not testing it thoroughly.

Before diving into what went wrong, I'll highlight the intended solution. These two challenges are a sequel to `good_trip`. Now, we can't trick the program by giving it a zero to mprotect; the program protects the memory itself:
```c
    read(0, code, 0x999);
    mprotect(code, 0x1000, PROT_READ | PROT_EXEC);
```
Additionally, PIE is enabled, and the only two addresses we know are `code` (our executable memory) and `edoc` (which serves as a fake stack). Before taking the player's input, the program sets a signal handler for SIGTRAP, which will come in handy later:
```c
    signal(SIGTRAP, debug);
```

The program takes code as input and filters it for `syscall`, `int 0x80`, and `sysenter`, making it unlikely to call a syscall directly. We need to find another way.

The inspiration for this challenge came from an amazing find by `vusec`, a Systems and Network Security Group at Vrije Universiteit Amsterdam. They discovered an MMU cache side-channel attack to bypass ASLR. You can read more in their [paper](https://download.vusec.net/papers/anc_ndss17.pdf).

So, we are given a confined sandbox. We can't execute arbitrary code, we don't know where we are, and we can't leak anything directly. 
But using the knowledge from the paper, we know we must bruteforce ASLR by capturing each TLB miss time until we get an address from the MMU cache. Once we get it, we know the address exists because of the dramatic decrease in fetch time.

The challenge provides a partial leak of `puts` to minimize bruteforcing.

Once we implement our code, we may notice that sometimes we hit the right address, but the fetching time doesn't decrease. I'm not entirely sure why, but it seems the MMU cache keeps caching addresses and deleting old ones in a FIFO manner. I must do more research on this.

By trial and error, I found that there's a way to call a libc function to keep the cache: the holy `int3` instruction. This instruction is used by debuggers to send a SIGTRAP to the program.

So, we can fetch the `puts` address every time by calling `int3`.

Easier said than done, the shellcode was a bit of a pain to write.

## Unintended Solutions
Now, for the unintended solutions. I was so focused on making the challenge stable that I completely forgot to zero out multiple registers (r13, fs_base, xmm0), which made the challenge much easier.

Well, I apologize for not testing rigorously. I owe you all an apology for the oversight.