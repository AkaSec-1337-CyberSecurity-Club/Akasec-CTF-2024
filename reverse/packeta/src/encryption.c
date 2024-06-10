#include "../headers/header.h"

void encryption(char *data, u_int64_t size)
{
    unsigned char tmp = 0;
    for (u_int64_t i = 0; i < size; i++)
    {
        tmp = data[i];
        for (u_int64_t j = 0; j < (sizeof(encryption_key) / sizeof(encryption_key[0])); j++)
        {
            tmp = tmp ^ encryption_key[j];
        }
        data[i] = ((tmp >> 2) | (tmp << (8 - 2)));
    }
}

static int is_text_section(const char *to_find)
{
    if (!strcmp(".text", to_find) || !strcmp(".data", to_find) || !strcmp(".rodata", to_find))
        return 1;
    return 0;
}


void section_encryption(t_file binary)
{
    char *section_name;

    for (size_t i = 0; i < binary.elf_header->e_shnum; i++)
    {
        section_name = get_section_name(binary.mapped_elf_ptr, binary.elf_sections[binary.elf_header->e_shstrndx], binary.elf_sections[i]->sh_name);
        if (is_text_section(section_name))
        { 
            RC4((binary.mapped_elf_ptr + binary.elf_sections[i]->sh_offset), binary.elf_sections[i]->sh_size);
        }
        free(section_name);
    }

}



