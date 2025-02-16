#ifndef INPUT_H_
#define INPUT_H_

#ifdef _WIN32
    #include <windows.h>
    void input_keyboard_press(uint32_t key_code, LPARAM lParam);
#endif

#ifdef __APPLE__
    void input_keyboard_press(uint32_t key_code); // src/mowi/window.m
#endif

void input_mouse_lmb_click(int x, int y);
void input_mouse_rmb_click(int x, int y);
void input_mouse_move(int x, int y);

#endif
