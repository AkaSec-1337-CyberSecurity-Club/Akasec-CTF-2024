#ifndef ELF_H
#define ELF_H
#include <stdint.h>

typedef struct s_elf64_hdr
{
    uint8_t e_ident[16];  /* Magic number and other info */
    uint16_t e_type;      /* Object file type */
    uint16_t e_machine;   /* Architecture */
    uint32_t e_version;   /* Object file version */
    uint64_t e_entry;     /* Entry point virtual address */
    uint64_t e_phoff;     /* Program header table file offset */
    uint64_t e_shoff;     /* Section header table file offset */
    uint32_t e_flags;     /* Processor-specific flags */
    uint16_t e_ehsize;    /* ELF header size in bytes */
    uint16_t e_phentsize; /* Program header table entry size */
    uint16_t e_phnum;     /* Program header table entry count */
    uint16_t e_shentsize; /* Section header table entry size */
    uint16_t e_shnum;     /* Section header table entry count */
    uint16_t e_shstrndx;  /* Section header string table index */
} t_elf64_hdr;

typedef struct s_elf64_phdr
{
    uint32_t p_type;
    uint32_t p_flags;
    u_int64_t p_offset; /* Segment file offset */
    u_int64_t p_vaddr;  /* Segment virtual address */
    u_int64_t p_paddr;  /* Segment physical address */
    u_int64_t p_filesz; /* Segment size in file */
    u_int64_t p_memsz;  /* Segment size in memory */
    u_int64_t p_align;  /* Segment alignment, file & memory */
} t_elf64_phdr;

typedef struct s_elf64_shdr
{
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
} t_elf64_shdr;

typedef struct s_file
{
    int fd;
    char *mapped_elf_ptr;
    off_t file_size;
    t_elf64_hdr *elf_header;
    t_elf64_shdr **elf_sections;
    t_elf64_phdr **elf_segments;
} t_file;

#endif