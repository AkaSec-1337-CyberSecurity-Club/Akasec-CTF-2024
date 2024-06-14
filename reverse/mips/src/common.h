#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <libdragon.h>

extern display_context_t display_ctx;

char* str_concatenate(char* array[], const char* joint);
int text_get_word_width(const char s[]);
void text_draw_wordwrap(int x, int y, int w, const char s[]);

#endif
