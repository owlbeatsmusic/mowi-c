#ifndef WINDOW_H_
#define WINDOW_H_

extern const uint32_t WINDOW_WIDTH;
extern const uint32_t WINDOW_HEIGHT;


#ifdef _WIN32
    #include <windows.h>

    extern HWND window_handle;
    extern HFONT h_font; // initialized later

    extern int WINAPI window_RunWindow(HINSTANCE hInstance, int nCmdShow);
#endif

#ifdef __APPLE__
    //int window_create(); // src/mowi/window.m
#endif

#endif
