#ifndef PARSER_H
#define PARSER_H

#include "../headers/elf.h"

int parse_header(char *mapped_elf_ptr, t_elf64_hdr *elf_header);
void parse_sections(t_file binary);
char *get_section_name(char *mapped_elf_ptr, t_elf64_shdr *shstrtab, uint32_t sh_name);

#endif