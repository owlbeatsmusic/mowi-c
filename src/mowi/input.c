#include <stdio.h>

#include "mowi/widget.h"
#include "mowi/mowi.h"
#include "mowi/window.h"
#include "common/color.h"
#include "mowi/renderer.h"

int screen_x = 0;
int screen_y = 0;

void input_click_widget(Widget widget) {
	switch (widget.type) {
		case MOWI_TEXT: { break; }
		case MOWI_RECT: { break; }
		case MOWI_HALF_RECT: { break; }
		case MOWI_ACTION_BUTTON: {

			break;
		}
		case MOWI_TOGGLE_BUTTON: {

			break;
		}
		case MOWI_LIST_BOX: {

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
}


#ifdef _WIN32

    #include <windows.h>

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
#endif

#ifdef __APPLE__

    void input_keyboard_press(uint32_t key_code) {

    }

#endif


void input_mouse_lmb_click(int x, int y) {
    screen_x = x / 9;
    screen_y = y / 20;
    for (int i = 0; i < widgets_length; i++) {
        input_click_widget(widgets[i]);
    }

}

void input_mouse_rmb_click(int x, int y) {
    screen_x = x / 9;
    screen_y = y / 20;

}

void input_mouse_move(int x, int y) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {

        screen_x = x / 9;
        screen_y = y / 20;

        for (int i = 0; i < widgets_length; i++) {
            renderer_hover_widget(widgets[i]);
        }
    }
}