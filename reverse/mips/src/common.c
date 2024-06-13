#include "common.h"

char* str_concatenate(char* array[], const char* joint) {
    int joint_len = strlen(joint);
    int total_len = 1;
    int size = 0;
    for (; array[size]; size++);
    int lengths[size];
    for (size_t i = 0; i < size; ++i) {
        lengths[i] = strlen(array[i]);
        total_len += lengths[i] + joint_len;
    }
    total_len -= joint_len;
    char* ret = malloc(total_len * sizeof(char));
    char* curr_pos = ret;
    for (size_t i = 0; i < size; ++i) {
        memcpy(curr_pos, array[i], lengths[i]);
        curr_pos += lengths[i];
        if (i < size - 1) {
            memcpy(curr_pos, joint, joint_len);
            curr_pos += joint_len;
        }
    }
    *curr_pos = '\0';
    return ret;
}

int text_get_word_width(const char* s) {
    int width = 0;
    for (size_t i = 0; s[i] && s[i] != '\n' && s[i] != ' '; i++)
        width += 7;
    return width;
}

void text_draw_wordwrap(int x, int y, int width, const char* text) {
    int x_off = 0;
    int y_off = 0;
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] == '\n' || (text[i] == ' ' && text_get_word_width(&text[i + 1]) > width - x_off - 3)) {
            x_off = 0;
            y_off += 11;
            continue;
        }
        if (width - x_off < 7) {
            x_off = 0;
            y_off += 11;
        }
        graphics_draw_character(display_ctx, x + x_off, y + y_off, text[i]);
        x_off += 7;
    }
}