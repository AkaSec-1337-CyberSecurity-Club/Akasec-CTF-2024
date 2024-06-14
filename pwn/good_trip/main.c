#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SYSCALL "\x0F\x05"
#define SYSENTER "\x0F\x34"
#define INT0x80 "\xcd\x80"

void exec(void *(code)()){
	asm volatile ("mov $0x0, %rbx");
	asm volatile ("mov $0x0, %r15");
	asm volatile ("mov $0x0, %rsp");
	asm volatile ("mov $0x0, %r14");
	asm volatile ("mov $0x0, %r8");
	asm volatile ("mov $0x0, %r11");
	asm volatile ("mov $0x0, %r12");
	asm volatile ("mov $0x0, %rbp");
	asm volatile ("jmp *%rdi");
}

bool filter(char *code){
	int i = -1;
	char *banned[] = {SYSCALL, SYSENTER, INT0x80};
	while (++i < 0x1000 - 2){
		int x = -1;
		while (++x < 3){
			if (memcmp(banned[x], &code[i], 2) == 0)
				return (true);
		}
	}
	return (false);
}

void init(){
        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);
}


int main(){
	int code_size = 0;
	init();
	void *code = mmap((void *)0x1337131369, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_PRIVATE|MAP_ANONYMOUS, -1 , 0);
	printf("code size >> ");
	scanf("%d", &code_size);
	if (code_size < 0 || code_size > 0x1000)
		return (0);
	printf("code >> ");
	read(0, code, 0x999);
	mprotect(code, code_size, PROT_READ | PROT_EXEC);
	if (filter(code) == true){
		printf("nop, not happening.\n");
		exit(-1);
	}
	exec(code);
}
