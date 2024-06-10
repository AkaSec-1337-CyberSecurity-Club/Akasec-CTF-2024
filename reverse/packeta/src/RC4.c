#include "../headers/header.h"

#define N 256 // 2^8

static void swap(unsigned char *a, unsigned char *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void KSA(const unsigned char *key, unsigned char *S)
{

    int len = strlen((const char *)key);
    int j = 0;

    for (int i = 0; i < N; i++)
        S[i] = i;

    for (int i = 0; i < N; i++)
    {
        j = (j + S[i] + key[i % len]) % N;
        swap(&S[i], &S[j]);
    }
}

void PRGA(unsigned char *S, char *data, u_int64_t size)
{

    int i = 0;
    int j = 0;

    for (u_int64_t n = 0; n < size; n++)
    {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];
        data[n] = rnd ^ data[n];
    }
}

void RC4(char *data, u_int64_t size)
{
    unsigned char S[N];
    KSA(encryption_key, S);
    PRGA(S, data, size);
}