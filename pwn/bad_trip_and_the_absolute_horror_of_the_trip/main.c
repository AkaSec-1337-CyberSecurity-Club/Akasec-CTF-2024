#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define SYSCALL "\x0F\x05"
#define SYSENTER "\x0F\x34"
#define INT0x80 "\xcd\x80"

bool meme = false;
char *code;


void debug(){
	printf("debug not available yet\n");
}

void exec(void *code){
	asm volatile ("mov $0x0, %rbx");
	asm volatile ("mov $0x0, %r15");
	asm volatile ("mov $0x0, %r14");
	asm volatile ("mov $0x0, %r9");
	asm volatile ("mov $0x0, %r8");
	asm volatile ("mov $0x0, %r11");
	asm volatile ("mov $0x0, %r12");
	asm volatile ("mov $0x0, %rsp");
	asm volatile ("mov $0x0, %rbp");
	asm volatile ("jmp *%rdi");
}

void init(){
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
	signal(SIGTRAP, debug);
}


bool filter(){
	int i = -1;
	char *banned[] = {SYSCALL, SYSENTER, INT0x80};
	while (++i < 0x1000 - 1){
		int x = -1;
		while (++x < 3){
			if (memcmp(banned[x], &code[i], 2) == 0){
				printf("nop, not happening.\n");
				exit(-1);
			}
		}
	}
	return (false);
}

int main(){
	init();
	code = mmap((void *)0x1337131369, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_PRIVATE|MAP_ANONYMOUS, -1 , 0);
	void *edoc = mmap((void *)0x6969696969, 0x21000, PROT_READ | PROT_WRITE,
			MAP_PRIVATE|MAP_ANONYMOUS, -1 , 0);

	printf("here ill give you something to start with %p\n", (uint64_t)puts & 0x0000ffffffff);
	printf("code >> ");
	read(0, code, 0x999);
	mprotect(code, 0x1000, PROT_READ | PROT_EXEC);

	filter();
	exec(code);
}
