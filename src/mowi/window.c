#pragma comment(lib, "Comctl32.lib")

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <commctrl.h>
#include <gl/gl.h>
#include <stdint.h>

#include "mowi/mowi.h"
#include "mowi/input.h"
#include "mowi/renderer.h"

const uint32_t WINDOW_WIDTH = 1024;
const uint32_t WINDOW_HEIGHT = 768;

static bool quit = false;

HWND window_handle;
HFONT h_font = NULL; // initialized later



// Custom Paint for Edit Control
LRESULT CALLBACK SubclassEditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    switch (message) {

        case WM_PAINT: {
			renderer_render_screen();
			mowi_redraw_tick();
            return 0;
        }
        case WM_NCDESTROY:
            RemoveWindowSubclass(window_handle, SubclassEditProc, uIdSubclass);
            break;
    }
    return DefSubclassProc(window_handle, message, wParam, lParam);
}


LRESULT CALLBACK WindowsProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam);

// this is the new main function called by windows
int WINAPI window_RunWindow(HINSTANCE hInstance, int nCmdShow) {

	static WNDCLASS window_class = { 0 };
	static const wchar_t window_class_name[] = L"My Window Class";
	window_class.lpszClassName = (PCSTR)window_class_name;
	window_class.lpfnWndProc = WindowsProcessMessage;
	window_class.hInstance = hInstance;

	RegisterClass(&window_class);

	window_handle =
		CreateWindow((PCSTR)window_class_name, "Fönsternamn", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	if (window_handle == NULL) { return -1; }

    /* HWND textbox_handle = 
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, window_handle, (HMENU)1, hInstance, NULL);
	if (textbox_handle == NULL) { return -1; }
	*/

    h_font = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Consolas");

    SetWindowSubclass(window_handle, SubclassEditProc, 1, 0);

	// setup för openGL
	HDC hdc = GetDC(window_handle);
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	HGLRC hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);


	// tillbaka till windows
	ShowWindow(window_handle, nCmdShow);

	while (!quit) {
		static MSG message = { 0 };
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		mowi_tick();

		//glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//SwapBuffers(hdc);
	}

	// Clean up OpenGL
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc);
	ReleaseDC(window_handle, hdc);

	return 0;
}

LRESULT CALLBACK WindowsProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_KEYDOWN: {
			input_keyboard_press((uint32_t)wParam, lParam);
			break;
		}
		case WM_LBUTTONDOWN: {  // Left mouse button click
			input_mouse_lmb_click(LOWORD(lParam), HIWORD(lParam));
			break;
        }

        case WM_RBUTTONDOWN: {  // Right mouse button click
            input_mouse_rmb_click(LOWORD(lParam), HIWORD(lParam));
			break;
        }

        case WM_MOUSEMOVE: {  // Mouse movement
            input_mouse_move(LOWORD(lParam), HIWORD(lParam));
			break;
        }

		case WM_QUIT:
		case WM_DESTROY: {
			quit = true;
		} break;	

		default: { // message not handled; pass on to default message handling function
			return DefWindowProc(window_handle, message, wParam, lParam);
		} break;
	}
	return 0;
}