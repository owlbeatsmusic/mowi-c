#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <gl/gl.h>

#include "common/color.h"
#include "mowi/window.h"
#include "mowi/mowi.h"

Pixel screen_grid[SCREEN_ROWS][SCREEN_COLUMNS];

void mowi_redraw_tick(void) {
    
}

void mowi_tick(void) { 

}

void mowi_create(void) {

    for (int y = 0; y < SCREEN_ROWS; y++) {
        for (int x = 0; x < SCREEN_COLUMNS; x++) {
            screen_grid[y][x].symbol = '#';
            screen_grid[y][x].color = FADED_WHITE;
        }
    }
    

    #ifdef _WIN32
        HINSTANCE hInstance = GetModuleHandle(NULL);
        window_RunWindow(hInstance, SW_SHOWDEFAULT);
    #endif


}