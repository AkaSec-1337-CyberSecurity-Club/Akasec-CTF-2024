#include <stdio.h>

char flag_1[] = "AKASEC{";
int flag_2[] = {0x2a, 0x76, 0x2e, 0x24, 0x1d, 0x32, 0x76, 0x21, 0x29, 0x1d, 0x2a, 0x76, 0x2e};
int main ( ) {
    int flag_3[] = {0x24, 0x1d, 0x75, 0x2a, 0x71, 0x1d, 0x24, 0x2e, 0x76, 0x74, 0x42};
    printf("%s",flag_1);
    for (int i = 0 ; i < 13 ; i++) {
        printf("%c", flag_2[i] ^ 0x42);
    };
     for (int i = 0 ; i < 11 ; i++) {
        printf("%c", flag_3[i] ^ 0x42);
    }
    printf("}");
}