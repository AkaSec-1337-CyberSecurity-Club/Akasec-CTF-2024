#include "common.h"

#define FPS_MAX 30

#define CON_A 4
#define CON_B 7
#define CON_Z 3
#define CON_DPAD_UP 2
#define CON_DPAD_DOWN 1
#define CON_DPAD_LEFT 5
#define CON_DPAD_RIGHT 9
#define CON_CUP 10
#define CON_CDOWN 15
#define CON_CLEFT 20
#define CON_CRIGHT 25
#define CON_LR 11
#define CON_RR 12

uint8_t valid_inp[] = {CON_Z, CON_RR, CON_CUP, CON_CUP, CON_CUP, CON_CUP, CON_CLEFT, CON_DPAD_DOWN, CON_DPAD_DOWN, CON_CUP,
        CON_A, CON_B, CON_CRIGHT, CON_DPAD_RIGHT, CON_DPAD_DOWN, CON_CUP, CON_DPAD_UP, CON_DPAD_LEFT, CON_DPAD_RIGHT, CON_B, 
        CON_DPAD_UP, CON_RR, CON_DPAD_RIGHT, CON_B, CON_CUP, CON_RR, CON_CUP, CON_Z, CON_DPAD_RIGHT, CON_Z};
uint8_t user_inp[30];
uint8_t user_inp_count = 0;
uint8_t solved = false;
const char* state_txt = "";
sprite_t* logo_sprite;
int64_t last_frame_tick = 0;
float average_fps = 0.0;
display_context_t display_ctx;
char* button_mappings[] = {"D", "U", "Z", "A", "L", "", "B", "", "R", "CU", "LR", "RR", "", "", "CD", "", "", "", "", "CL", "", "", "", "", "CR"};

bool fps_frame_lock() {
    int64_t current_tick = timer_ticks();
    if (current_tick >= last_frame_tick + (TICKS_PER_SECOND / FPS_MAX)) {
        average_fps = (float)(TICKS_PER_SECOND) / (current_tick - last_frame_tick);
        last_frame_tick = current_tick;
        return false;
    }
    return true;
}

bool gfx_display_lock(display_context_t disp) {
    if (!(disp = display_get())) return true;
    display_ctx = disp;
    return false;
}

void gfx_display_flip() {
    if (!display_ctx) return;
    display_show(display_ctx);
    display_ctx = 0;
}

uint8_t get_last_button_held(struct controller_data keys) {
    if (keys.c[0].A)
        return CON_A;
    if (keys.c[0].B)
        return CON_B;
    if (keys.c[0].up)
        return CON_DPAD_UP;
    if (keys.c[0].down)
        return CON_DPAD_DOWN;
    if (keys.c[0].left)
        return CON_DPAD_LEFT;
    if (keys.c[0].right)
        return CON_DPAD_RIGHT;
    if (keys.c[0].Z)
        return CON_Z;
    if (keys.c[0].C_up)
        return CON_CUP;
    if (keys.c[0].C_down)
        return CON_CDOWN;
    if (keys.c[0].C_left)
        return CON_CLEFT;
    if (keys.c[0].C_right)
        return CON_CRIGHT;
    if (keys.c[0].L)
        return CON_LR;
    if (keys.c[0].R)
        return CON_RR;
    return 0;
}

void render_main_screen() {
    graphics_fill_screen(display_ctx, 0x0);

    graphics_set_color(0xffffffff, 0x0);
    graphics_draw_text(display_ctx, 235, 225, "welcome!");
    graphics_draw_text(display_ctx, 10, 20, "input the correct button combo:");
    
    char* arr[30] = {0};
    for (size_t i = 0; i < 30 && user_inp[i] != 0; i++)
        arr[i] = button_mappings[user_inp[i] - 1];
    
    char* inp_str = str_concatenate(arr, " ");
    text_draw_wordwrap(10, 40, 210, inp_str);
    free(inp_str);
    
    graphics_draw_sprite(display_ctx, 135, 205, logo_sprite);
    graphics_set_color(solved ? 0x5cfa6fff :  0xfc554cff, 0x0);
    graphics_draw_text(display_ctx, 10, 225, state_txt);
}

void append_user_inp() {
    struct controller_data keys = get_keys_down();
    if (solved || !keys.c[0].data)
        return;
    if (!user_inp_count)
        memset(user_inp, 0, 30 * sizeof(uint8_t));
    user_inp[user_inp_count] = get_last_button_held(keys);
    user_inp_count++;
    if (user_inp_count == 30) {
        if (!memcmp(user_inp, valid_inp, 30)) {
            state_txt = "correct!";
            solved = true;
            return;
        }
        state_txt = "wrong";
        user_inp_count = 0;
    }
}

void update() {
    controller_scan();
    
    append_user_inp();
    graphics_set_color(0xffffffff, 0);
    graphics_fill_screen(display_ctx, 0x0);
    
    render_main_screen();
    
    gfx_display_flip();
}

int main() {
    timer_init();
    controller_init();
    dfs_init(DFS_DEFAULT_LOCATION);
    
    int sprite_handle = dfs_open("/akasec.sprite");
    logo_sprite = malloc(dfs_size(sprite_handle));
    dfs_read(logo_sprite, 1, dfs_size(sprite_handle), sprite_handle);
    dfs_close(sprite_handle);

    display_init(RESOLUTION_320x240, DEPTH_32_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    controller_scan();

    while (1) {
        static display_context_t disp = 0;
        while (gfx_display_lock(disp));
        while (fps_frame_lock());
        update();
    }
}