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
	screen_grid[y][x].color = color;
}

void mowi_redraw_tick(void) {
    
}

void mowi_tick(void) { 
    
}

void test_on_click() {
    printf("action button click!\n");
}

void mowi_add_widget(Widget *widget) {
    for (int i = 0; i < 64; i++) {
        if (widgets[i].type == NONE) {
            widgets[i] = *widget;
            widgets_length++;
            switch (widgets[i].type) {
                case MOWI_LIST_BOX: {
                    for (int j = 0; j < widgets[i].list_box_length; j++) {
                        BoxOption option = { .index = j, .is_selected = 0, .title_length=strlen(widgets[i].list_box_all_options[j]) };
                        strcpy(option.title, widgets[i].list_box_all_options[j]);
                        widgets[i].list_box_options_internal[j] = option;   
                    }
                    break;
                }
                case MOWI_RADIAL_BOX: {
                    
                    break;
                }
                case MOWI_SLIDER: {
                    
                    break;
                }
                case MOWI_TEXT_BOX: {
                    
                    break;
                }
                case MOWI_CONSOLE: {
                    
                    break;
                }
            }
            break;
        }
    }
}

void mowi_create(void) {

    Widget toggle = {
        .type = MOWI_TOGGLE_BUTTON,
        .x = 14,
        .y = 13,
        .toggle_button_title = "Toggle Button",
        .toggle_button_title_length = 13,
        .toggle_button_state = 0,
        //.action_button_on_click = &test_on_click
    };
    mowi_add_widget(&toggle);

    uint16_t  list_box_length;
    uint16_t  list_box_selected_options_count;
    char      list_box_title[64];
    char      list_box_all_options[32][64];
    char      list_box_selected_options[32][64];
    BoxOption list_box_options_internal[64];

    Widget list_box = {
        .type = MOWI_LIST_BOX,
        .x = 35,
        .y = 13,
        .list_box_length = 5,
        .list_box_selected_options_count = 0,
        .list_box_title = "ListBox",
        .list_box_all_options = {"Option", "Alternativ", "Test", "Hejsan", "Detta"}
    };
    mowi_add_widget(&list_box);

    default_fg_color        = WHITE;
    default_fg_faded_color  = FADED_WHITE;
    default_bg_color        = BLACK;
    default_bg_faded_color  = FADED_BLACK;
    default_pop_color       = GREEN;
    default_pop_faded_color = FADED_GREEN;

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