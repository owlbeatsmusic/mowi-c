#include <windows.h>

#include "mowi/window.h"

void mowi_create(void) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    RunWindow(hInstance, SW_SHOWDEFAULT);
}