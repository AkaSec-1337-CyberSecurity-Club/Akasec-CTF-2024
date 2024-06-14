#include <stdio.h>

char name[0x200];

void okey(){
	asm(
		"pop %rsp;"
		"ret;"
	);
}

void helper(){
	setvbuf(stdin, 0, _IONBF, 0);
	setvbuf(stdout, 0, _IONBF, 0);
	return;
}


int main(){
	char flow[63];

	helper();
	printf("%p\n", puts);
	printf("name>> ");
	fgets(name, 0x200, stdin);
	printf("alright>> ");
	fgets(flow, 64 + 24, stdin);
	printf("okey\n");
}
