// gcc main.c -s -o chall

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>

__attribute__((constructor)) void ctor() {
    long result;
    __asm__ volatile (
        "mov $101, %%rax\n"  
        "xor %%rdi, %%rdi\n" 
        "xor %%rsi, %%rsi\n" 
        "xor %%rdx, %%rdx\n" 
        "xor %%r10, %%r10\n" 
        "syscall\n"          
        : "=a" (result) :: "%rdi", "%rsi", "%rdx", "%r10"
    );

    if (result < 0) {
        printf(":3\n");
        exit(0);
    }
}

int main() {
    unsigned char code[] = {167, 186, 123, 23, 186, 113, 30, 178, 150, 186, 121, 246, 215, 218, 242, 242, 242, 186, 123,
                            183, 10, 195, 50, 186, 74, 209, 219, 209, 195, 213, 211, 203, 195, 186, 72, 216, 129, 196, 196,
                            201, 239, 192, 132, 186, 123, 183, 34, 186, 123, 167, 42, 186, 74, 201, 239, 192, 132, 211, 219,
                            131, 212, 186, 72, 239, 210, 129, 222, 132, 194, 201, 205, 186, 123, 183, 46, 186, 123, 167, 22,
                            53, 183, 62, 242, 242, 242, 242, 25, 234, 121, 183, 62, 253, 68, 182, 247, 34, 113, 2, 176, 123,
                            48, 121, 183, 62, 122, 166, 247, 34, 113, 183, 62, 243, 113, 143, 62, 233, 132, 16, 98, 186, 121,
                            183, 10, 150, 186, 217, 246, 215, 218, 242, 242, 242, 134, 247, 26, 242, 242, 242, 242, 59, 49};
    typedef void (*func)();
    for (size_t i = 0; i < 141; i++)
        code[i] ^= 0xf2;
    void* pg = mmap(NULL, sizeof(code), PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(pg, code, sizeof(code));
    func f = (func)pg;
    f();
    printf(":3\n");
    return 0;
}
