#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>


#include <stddef.h>

#include "../headers/elf.h"
#include "../headers/parser.h"

#define PAGE_SIZE 4096

extern unsigned char encryption_key[16];


void encryption(char *data, u_int64_t size);
void section_encryption(t_file binary);
void generate_random_key();
void RC4(char *data, u_int64_t size);
void write_to_new_file(t_file  *binary) ;
#endif