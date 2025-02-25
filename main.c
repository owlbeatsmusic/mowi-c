/* WIN32
cl .\main.c /link opengl32.lib gdi32.lib user32.lib
*/

/* APPLE
clang -I./include -I./lib ./src/main.c ./src/mowi/mowi.c ./src/mowi/window.c ./src/mowi/input.c ./src/mowi/window.m ./src/mowi/renderer.c ./src/common/color.c ./src/common/print.c -framework Cocoa -o mowi
*/

#include  <stdio.h>

#define MOWI_IMPLEMENTATION
#include "mowi.h"

ActionButton action;
ToggleButton toggle;

void test_on_click(void) {
    printf("toggle: %d\n", toggle.state);
}

int main(void) {

    /*
    
    TODO:
        - Implemenet all widgets
        - Setting window properties by function
        - Refactoring to specify MoWi
        - Documentation
    */

    widget_create_action_button(&action, 14, 4, "Action Button", &test_on_click); 
    widget_create_toggle_button(&toggle, 14, 3, "Toggle Button");

    mowi_create("MoWi UI Module testwindow");

    return 0;
}


