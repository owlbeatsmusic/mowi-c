# MoWi UI Library (C) - WINDOWS ONLY
MoWi is a minimal and text-based UI-library that is not terminal-based. MoWi is for now WINDOWS ONLY. This UI-library is not intended for serious applications but is still easy to use for simple applications and code-testing.

All widgets need to be created before creating the mowi-window. 

Example:
![example output window of MoWi](https://github.com/owlbeatsmusic/mowi-c/blob/main/docs/images/Screenshot_2025-02-19.png?raw=true)
Source:
```c
#include <stdio.h>
#include "mowi.h"

ActionButton action;
ToggleButton toggle;

void test_on_click(void) {
    printf("toggle: %d\n", toggle.state);
}

int main(void) {
    widget_create_action_button(&action, 14, 4, "Action Button", &test_on_click); 
    widget_create_toggle_button(&toggle, 14, 3, "Toggle Button");

    mowi_create("MoWi UI Module testwindow");

    return 0;
}
```

## How to use
Just add the `mowi.h` to your project directory and compile with:
```shell
cl main.c /link opengl32.lib gdi32.lib user32.lib`
```

