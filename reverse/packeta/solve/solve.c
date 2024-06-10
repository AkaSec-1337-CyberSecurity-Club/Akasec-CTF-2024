#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define START_TIME 0x1337
#define NUM_SEEDS 100000
#define KEY_LENGTH 16

typedef unsigned long long uint64_t;

typedef struct s_encrypted_section {
    uint64_t size;
    uint64_t address;
} t_encrypted_section;

static void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

static void KSA(unsigned char *S, const char *key) {
    int len = strlen(key);
    int j = 0;

    for (int i = 0; i < 256; i++)
        S[i] = i;

    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % len]) % 256;
        swap(&S[i], &S[j]);
    }
}

static void PRGA(unsigned char *S, char *data, unsigned int size) {
    int i = 0;
    int j = 0;

    for (unsigned int n = 0; n < size; n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % 256];
        data[n] = rnd ^ data[n];
    }
}

void RC4(char *data, uint64_t size, const char *key) {
    unsigned char S[256];
    KSA(S, key);
    PRGA(S, data, size);
}

void generate_key(char *key, unsigned int seed) {
    srand(seed);
    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < KEY_LENGTH; ++i) {
        key[i] = charset[rand() % charsetSize];
    }
    key[KEY_LENGTH] = '\0';
}

int test_decryption(const char *key, char *mapped_elf_ptr, uint64_t file_size, uint64_t text_offset, uint64_t text_size, uint64_t data_offset, uint64_t data_size, uint64_t rodata_offset, uint64_t rodata_size) {
    int fd = open("temp_solved", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fd == -1) {
        perror("Failed to create temporary file");
        return 0;
    }

    char *temp_buffer = malloc(file_size);
    if (!temp_buffer) {
        perror("Failed to allocate memory");
        close(fd);
        return 0;
    }
    memcpy(temp_buffer, mapped_elf_ptr, file_size);

    RC4(temp_buffer + text_offset, text_size, key);
    RC4(temp_buffer + data_offset, data_size, key);
    RC4(temp_buffer + rodata_offset, rodata_size, key);

    if (write(fd, temp_buffer, file_size) == -1) {
        perror("Failed to write to temporary file");
        free(temp_buffer);
        close(fd);
        return 0;
    }

    close(fd);
    free(temp_buffer);

    pid_t pid = fork();
    if (pid == 0) {
        execl("./temp_solved", "./temp_solved", (char *)NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    uint64_t text_offset = 0x1060;
    uint64_t text_size = 0x1c7;
    uint64_t data_offset = 0x2000;
    uint64_t data_size = 0x7;
    uint64_t rodata_offset = 0x3020;
    uint64_t rodata_size = 0x74;

    int fd;
    char *mapped_elf_ptr = NULL;
    fd = open("new", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    uint64_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Failed to get file size");
        close(fd);
        exit(EXIT_FAILURE);
    }

    mapped_elf_ptr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mapped_elf_ptr == MAP_FAILED) {
        perror("Failed to map file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    char key[KEY_LENGTH + 1];
    for (unsigned int i = 0; i < 500; ++i) {
        unsigned int seed = START_TIME + i;
        generate_key(key, seed);
        if (test_decryption(key, mapped_elf_ptr, file_size, text_offset, text_size, data_offset, data_size, rodata_offset, rodata_size)) {
            printf("Found correct key: %s\n", key);
            break;
        }
    }

    munmap(mapped_elf_ptr, file_size);

    return 0;
}
