#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "common/print.h"
#include "common/color.h"
#include "mowi/window.h"
#include "mowi/widget.h"
#include "mowi/mowi.h"

#ifdef _WIN32
    #include <windows.h>
    #include <gl/gl.h>
#endif

Pixel screen_grid[SCREEN_ROWS][SCREEN_COLUMNS];

void mowi_set_pixel(int x, int y, char symbol, Color color) {
    screen_grid[y][x].symbol = symbol;
	screen_grid[y][x].color = default_fg_color;
}

void mowi_redraw_tick(void) {
    
}

void mowi_tick(void) { 
    
}

void mowi_create(void) {

    Widget test = {
        .type = MOWI_HALF_RECT,
        .x = 14,
        .y = 13,
        .rect_width = 3,
        .rect_height = 5,
    };
    widgets[0] = test;
    widgets_length++;

    default_fg_color       = WHITE;
    default_fg_faded_color = FADED_WHITE;
    default_bg_color       = BLACK;
    default_bg_faded_color = FADED_BLACK;

    for (int y = 0; y < SCREEN_ROWS; y++) {
        for (int x = 0; x < SCREEN_COLUMNS; x++) {
            mowi_set_pixel(x, y, ' ', FADED_WHITE);
        }
    }

    #ifdef _WIN32
        HINSTANCE hInstance = GetModuleHandle(NULL);
        window_RunWindow(hInstance, SW_SHOWDEFAULT);
    #endif


    #ifdef __APPLE__
        printf("%s mowi does not work on MacOS yet.\n", PRINT_WARNING);
    #endif


}