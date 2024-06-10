#include "../headers/header.h"

unsigned char encryption_key[16];

int main(int argc, char **argv)
{
    t_file binary;
    int fd;

    binary.mapped_elf_ptr = NULL;

    if (argc < 2)
    {
        printf("Usage:\n$> %s your_elf_binary", argv[0]);
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1], O_RDONLY);
    if (!fd)
    {
        exit(EXIT_FAILURE);
    }
    binary.file_size = lseek(fd, 0, SEEK_END);
    if (binary.file_size == -1)
    {
        close(fd);
        exit(EXIT_FAILURE);
    }
    binary.mapped_elf_ptr = mmap(NULL, binary.file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (binary.mapped_elf_ptr == MAP_FAILED)
    {
        exit(EXIT_FAILURE);
    }
    close(fd);
    binary.elf_header = malloc(sizeof(t_elf64_hdr));
    if (!binary.elf_header)
    {
        exit(EXIT_FAILURE);
    }

    if (!parse_header(binary.mapped_elf_ptr, binary.elf_header))
    {
        exit(EXIT_FAILURE);
    }

    binary.elf_sections = malloc(sizeof(t_elf64_shdr *) * binary.elf_header->e_shnum);
    if (!binary.elf_sections)
    {
        exit(EXIT_FAILURE);
    }

    binary.elf_segments = malloc(sizeof(t_elf64_phdr *) * binary.elf_header->e_phnum);
    if (!binary.elf_segments)
    {
        exit(EXIT_FAILURE);
    }
    parse_sections(binary);
    generate_random_key();
    section_encryption(binary);
    write_to_new_file(&binary);
}
