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

MowiPixel screen_grid[SCREEN_ROWS][SCREEN_COLUMNS];

void mowi_set_pixel_internal(int x, int y, char symbol, Color color) {
    screen_grid[y][x].symbol = symbol;
	screen_grid[y][x].color = color;
}

void mowi_redraw_tick_internal(void) {
    
}

void mowi_tick_internal(void) { 

}

void mowi_create(char window_title[]) {

    /*
    MowiWidget list_box = {
        .type = MOWI_LIST_BOX,
        .x = 35,
        .y = 13,
        .list_box_length = 5,
        .list_box_show_counter = true,
        .list_box_number_of_selections = 0,
        .list_box_title = "ListBox",
        .list_box_all_options = {"Option", "Alternativ", "Test", "Hejsan", "Detta"}
    };
    mowi_add_widget(list_box, 0);

    MowiWidget radial_box = {
        .type = MOWI_RADIAL_BOX,
        .x = 55,
        .y = 13,
        .radial_box_length = 5,
        .radial_box_show_selected_index = true,
        .radial_box_title = "RadialBox",
        .radial_box_all_options = {"Option", "Alternativ", "Test", "Hejsan", "Detta"}
    };
    mowi_add_widget(radial_box, 0);
    */



    default_fg_color        = WHITE;
    default_fg_faded_color  = FADED_WHITE;
    default_bg_color        = BLACK;
    default_bg_faded_color  = FADED_BLACK;
    default_pop_color       = GREEN;
    default_pop_faded_color = FADED_GREEN;

    for (int y = 0; y < SCREEN_ROWS; y++) {
        for (int x = 0; x < SCREEN_COLUMNS; x++) {
            mowi_set_pixel_internal(x, y, ' ', FADED_WHITE);
        }
    }

    #ifdef _WIN32
        HINSTANCE hInstance = GetModuleHandle(NULL);
        window_RunWindow(hInstance, SW_SHOWDEFAULT, window_title);
    #endif


    #ifdef __APPLE__
        printf("%s mowi does not work on MacOS yet.\n", PRINT_WARNING);
    #endif


}