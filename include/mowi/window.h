#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>

extern const uint32_t WINDOW_WIDTH;
extern const uint32_t WINDOW_HEIGHT;

extern HWND window_handle;
extern HFONT h_font; // initialized later

extern int WINAPI window_RunWindow(HINSTANCE hInstance, int nCmdShow);

#endif
