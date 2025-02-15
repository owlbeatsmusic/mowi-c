#include <windows.h>
#include <stdio.h>

#include "mowi/mowi.h"
#include "mowi/window.h"
#include "common/color.h"
#include "mowi/renderer.h"

void input_keyboard_press(uint32_t key_code, LPARAM lParam) {
    if (key_code == 27) {
        printf("ESCAPE!\n");
    }
    else {
        /* key-press to string */
        WCHAR key_name[128];
        int result = GetKeyNameTextW(lParam, key_name, sizeof(key_name) / sizeof(WCHAR));
        if (result > 0) {
            //wprintf(L"Key: %s\n", key_name);
        }
    }
}

void input_mouse_lmb_click(int x, int y) {
    //printf("(%d, %d)\n", x / 9, y / 20);

}

void input_mouse_rmb_click(int x, int y) {
    //printf("(%d, %d)\n", x / 9, y / 20);

}

void input_mouse_move(int x, int y) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {

        int screen_x = x / 9;
        int screen_y = y / 20;
        //printf("(%d, %d)\n", screen_x, screen_y);
        screen_grid[screen_y][screen_x].symbol = '*';
        screen_grid[screen_y][screen_x].color  = RED;

        renderer_set_pixel(screen_x, screen_y);

    }
    //renderer_render_screen();
}