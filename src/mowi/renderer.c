#include <windows.h>
#include <gl/gl.h>

#include "mowi/mowi.h"
#include "mowi/window.h"

void renderer_render_screen(void) {

    h_font = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Consolas");

    // Set the font on the control
    SendMessage(window_handle, WM_SETFONT, (WPARAM)h_font, TRUE);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(window_handle, &ps);

	HFONT oldFont = (HFONT)SelectObject(hdc, h_font);

	RECT rect;
	GetClientRect(window_handle, &rect);
	SetBkMode(hdc, TRANSPARENT);

	// Set custom background color
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdc, &rect, hBrush);
	DeleteObject(hBrush);

	// Draw each character in different colors
	int cy = 0; // height of character (consolas(20) -> width=9, height=20)
	int offset_x = 0;
	int offset_y = 0;
	for (int y = 0; y < SCREEN_ROWS; y++) {
		for (int x = 0; x < SCREEN_COLUMNS; x++) {
			
			SetTextColor(hdc, RGB(screen_grid[y][x].color.red, screen_grid[y][x].color.green, screen_grid[y][x].color.blue));
			char ch[2] = { screen_grid[y][x].symbol, '\0' };
			TextOut(hdc, offset_x, offset_y, ch, 1);
			
			SIZE text_size;
			GetTextExtentPoint32(hdc, ch, 1, &text_size);
			offset_x += text_size.cx; // Move to next character position				
			cy = text_size.cy;
		}
		offset_x = 0;
		offset_y += cy;
	}	

	EndPaint(window_handle, &ps);
}

void renderer_set_pixel(int x, int y) {

    HDC hdc = GetDC(window_handle);  // Use GetDC instead of BeginPaint

    h_font = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Consolas");
    SendMessage(window_handle, WM_SETFONT, (WPARAM)h_font, TRUE);
	HFONT oldFont = (HFONT)SelectObject(hdc, h_font);

    SetTextColor(hdc, RGB(screen_grid[y][x].color.red, screen_grid[y][x].color.green, screen_grid[y][x].color.blue));
    char ch[2] = { screen_grid[y][x].symbol, '\0' };

    SIZE text_size;
    GetTextExtentPoint32(hdc, ch, 1, &text_size);

    TextOut(hdc, x * text_size.cx, y * text_size.cy, ch, 1);  // Correct positioning

    ReleaseDC(window_handle, hdc);  // Release the HDC after use
}