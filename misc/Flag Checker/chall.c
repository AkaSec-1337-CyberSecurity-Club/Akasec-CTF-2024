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
}