// gcc main.c -o chall
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

const char* flag = "akasec{n0t_t00_m4ny_br41nc3lls_l3ft}";

int main() {
    srand(time(NULL));
    for (size_t i = 0; i < 36; i++)
        printf("%i ", flag[i] ^ (rand() % 256));
    printf("\n");
    return 0;
}
