
#include "../headers/header.h"

int parse_header(char *mapped_elf_ptr, t_elf64_hdr *elf_header)
{
    memcpy(elf_header, mapped_elf_ptr, sizeof(*elf_header));
    if (elf_header->e_ident[0] == 0x7f &&
        elf_header->e_ident[1] == 'E' &&
        elf_header->e_ident[2] == 'L' &&
        elf_header->e_ident[3] == 'F' &&
        elf_header->e_ident[4] == 2)
        return (1);
    else
        return (0);
}

void parse_sections(t_file binary)
{
    for (uint16_t i = 0; i < binary.elf_header->e_shnum; i++)
    {
        *(binary.elf_sections + i) = malloc(sizeof(t_elf64_shdr));
        if (!*(binary.elf_sections + i))
        {
            exit(EXIT_FAILURE);
        }
        memcpy(*(binary.elf_sections + i), (binary.mapped_elf_ptr + binary.elf_header->e_shoff + (i * binary.elf_header->e_shentsize)), sizeof(t_elf64_shdr));
    }
}

char *get_section_name(char *mapped_elf_ptr, t_elf64_shdr *shstrtab, uint32_t sh_name)
{

    uint32_t name_size = strlen((mapped_elf_ptr + shstrtab->sh_offset + sh_name));
    char *name = malloc(sizeof(char) * name_size);
    if (!name)
    {
        exit(EXIT_FAILURE);
    }
    memcpy(name, (mapped_elf_ptr + shstrtab->sh_offset + sh_name), name_size);
    return name;
}