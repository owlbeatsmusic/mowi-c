#pragma comment(lib, "Comctl32.lib")

#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <commctrl.h>
#include <gl/gl.h>
#include <stdint.h>

static bool quit = false;

static const char* display_text = "Colorful Text\nsdfsdf"; // Example text
static COLORREF colors[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0), RGB(255, 0, 255) };

HFONT h_font = NULL;

// Custom Paint for Edit Control
LRESULT CALLBACK SubclassEditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    switch (message) {
        case WM_CREATE: {
            // Create font once during initialization
            h_font = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                               OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Arial");

            // Set the font on the control
            SendMessage(hwnd, WM_SETFONT, (WPARAM)h_font, TRUE);
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            HFONT oldFont = (HFONT)SelectObject(hdc, h_font);

            RECT rect;
            GetClientRect(hwnd, &rect);
            SetBkMode(hdc, TRANSPARENT);

            // Set custom background color
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);

            // Draw each character in different colors
            int length = lstrlen(display_text);
            int x = 5; // Starting position
            for (int i = 0; i < length; i++) {
                SetTextColor(hdc, colors[i % (sizeof(colors) / sizeof(colors[0]))]);
                char ch[2] = { display_text[i], '\0' };
                TextOut(hdc, x, 5, ch, 1);
                SIZE textSize;
                GetTextExtentPoint32(hdc, ch, 1, &textSize);
                x += textSize.cx; // Move to next character position
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_NCDESTROY:
            RemoveWindowSubclass(hwnd, SubclassEditProc, uIdSubclass);
            break;
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}


LRESULT CALLBACK WindowsProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam);

// this is the new main function called by windows
int WINAPI RunWindow(HINSTANCE hInstance, int nCmdShow) {

	static WNDCLASS window_class = { 0 };
	static const wchar_t window_class_name[] = L"My Window Class";
	window_class.lpszClassName = (PCSTR)window_class_name;
	window_class.lpfnWndProc = WindowsProcessMessage;
	window_class.hInstance = hInstance;

	RegisterClass(&window_class);

    const uint32_t INITIAL_WINDOW_WIDTH = 1024;
    const uint32_t INITIAL_WINDOW_HEIGHT = 768;

	HWND window_handle =
		CreateWindow((PCSTR)window_class_name, "Fönsternamn", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	if (window_handle == NULL) { return -1; }

    HWND textbox_handle = 
    CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY, 0, 0, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, window_handle, (HMENU)1, hInstance, NULL);
	if (textbox_handle == NULL) { return -1; }

    h_font = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Consolas");

    SetWindowSubclass(textbox_handle, SubclassEditProc, 1, 0);

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
