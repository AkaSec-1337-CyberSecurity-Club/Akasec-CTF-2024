#include "../headers/header.h"


void generate_random_key()
{
    time_t start_time = 0x1337; 
    time_t current_time;

    time(&current_time);
    srand((unsigned int)(start_time + (current_time % (500))));

    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < 16; ++i)
    {
        encryption_key[i] = charset[rand() % charsetSize];
    }
}

void free_function(char *mapped_elf,t_file *binary) {
    if (mapped_elf)
    {
        munmap(mapped_elf,binary->file_size);
        mapped_elf = NULL;
    }
    if (binary->elf_sections)
    {
        for (uint16_t i = 0; i < binary->elf_header->e_shnum; i++)
        {
            if (binary->elf_sections[i])
            {
                free(binary->elf_sections[i]);
                binary->elf_sections[i] = NULL;
            }
        }
        free(binary->elf_sections);
        binary->elf_sections = NULL;
    }
    if (binary->elf_segments)
    {
        for (uint16_t i = 0; i < binary->elf_header->e_phnum; i++)
        {
            if (binary->elf_segments[i])
            {
                free(binary->elf_segments[i]);
                binary->elf_segments[i] = NULL;
            }
        }
        free(binary->elf_segments);
        binary->elf_segments = NULL;
    }
    if (binary->elf_header)
    {
        free(binary->elf_header);
        binary->elf_header = NULL;
    }
}

void write_to_new_file(t_file  *binary) {
    int fd;

    fd = open("new", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fd == -1)
    {
        exit(EXIT_FAILURE);
    }
    if (write(fd, binary->mapped_elf_ptr, binary->file_size) == -1)
    {
        exit(EXIT_FAILURE);
    }
    close(fd);
    free_function(binary->mapped_elf_ptr, binary);
    printf("Jogadinha do Packeta\n");
}