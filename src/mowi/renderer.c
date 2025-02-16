#include <stdio.h>
#include <string.h>

#include "common/color.h"
#include "mowi/widget.h"
#include "mowi/mowi.h"
#include "mowi/window.h"
#include "mowi/renderer.h"
#include "mowi/input.h"

void renderer_render_widget(Widget widget) {
	switch (widget.type) {
		case MOWI_TEXT: {
			for (int i = 0; i < widget.text_length; i ++) {
				mowi_set_pixel(widget.x+i, widget.y, widget.text[i], default_fg_color);
			}
			break;
		}
		case MOWI_RECT: {
			mowi_set_pixel(widget.x, 				   widget.y, 					    '.', default_fg_color);
			mowi_set_pixel(widget.x+widget.rect_width-1, widget.y,					    '.', default_fg_color);
			mowi_set_pixel(widget.x, 				   widget.y+widget.rect_height-1,   '\'', default_fg_color);
			mowi_set_pixel(widget.x+widget.rect_width-1, widget.y+widget.rect_height-1, '\'', default_fg_color);

			for (int i = 1; i < widget.rect_width-1; i++) {
				mowi_set_pixel(widget.x+i, widget.y, 					  '-', default_fg_color);
				mowi_set_pixel(widget.x+i, widget.y+widget.rect_height-1, '-', default_fg_color);
			}
			for (int i = 1; i < widget.rect_height-1; i++) {
				mowi_set_pixel(widget.x, widget.y+i, 					  '|', default_fg_color);
				mowi_set_pixel(widget.x+widget.rect_width-1, widget.y+i,  '|', default_fg_color);
			}

			break;
		}
		case MOWI_HALF_RECT: {
			mowi_set_pixel(widget.x, 				  		  widget.y, 					      '.', default_fg_color);
			mowi_set_pixel(widget.x+widget.half_rect_width-1, widget.y,					          '.', default_fg_color);
			mowi_set_pixel(widget.x, 				          widget.y+widget.half_rect_height-1, '\'', default_fg_color);
			mowi_set_pixel(widget.x+widget.half_rect_width-1, widget.y+widget.half_rect_height-1, '\'', default_fg_color);

			for (int i = 1; i < widget.half_rect_width-1; i++) {
				mowi_set_pixel(widget.x+i, widget.y, 				           '-', default_fg_color);
				mowi_set_pixel(widget.x+i, widget.y+widget.half_rect_height-1, '-', default_fg_color);
			}
			for (int i = 1; i < widget.half_rect_height-1; i++) {
				mowi_set_pixel(widget.x, widget.y+i, 					  '|', default_fg_color);
			}
			break;
		}
		case MOWI_ACTION_BUTTON: {
			for (int i = 0; i < widget.toggle_button_title_length; i ++) { // same as mowi_text :/
				mowi_set_pixel(widget.x+i, widget.y, widget.action_button_title[i], default_fg_color);
			}
			break;
		}
		case MOWI_TOGGLE_BUTTON: {
			Color color = default_fg_color;
			if (widget.toggle_button_state == 1) color = default_pop_color;
			for (int i = 0; i <  widget.toggle_button_title_length; i ++) { // same as mowi_text :/
				mowi_set_pixel(widget.x+i, widget.y, widget.toggle_button_title[i], color);
			}
			break;
		}
		case MOWI_LIST_BOX: {
			Widget half_rect = {.type = MOWI_HALF_RECT, .x = widget.x, .y = widget.y, .half_rect_width = 3, .half_rect_height = widget.list_box_length+2};
			renderer_render_widget(half_rect);

			// title
			mowi_set_pixel(widget.x+2, widget.y, '[', default_fg_color);
			for (int i = 0; i < strlen(widget.list_box_title); i ++) {
				mowi_set_pixel(widget.x+3+i, widget.y, widget.list_box_title[i], default_fg_color);
			}
			mowi_set_pixel(widget.x+3+strlen(widget.list_box_title), widget.y, ']', default_fg_color);

			// options
			for (int i = 0; i < widget.list_box_length; i ++) {
				if (widget.list_box_options_internal[i].is_selected == 1) {
					mowi_set_pixel(widget.x+1, widget.y+1+i, '>', default_pop_color);
				}
				else {
					mowi_set_pixel(widget.x+1, widget.y+1+i, ' ', default_fg_color);
				}
				for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
                    mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
                }
			}

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

void renderer_hover_widget(Widget widget) {
	switch (widget.type) {
		case MOWI_TEXT: { break; }
		case MOWI_RECT: { break; }
		case MOWI_HALF_RECT: { break; }
		case MOWI_ACTION_BUTTON: {
			if (screen_x >= widget.x && screen_x < widget.x+widget.action_button_title_length && screen_y == widget.y) {
				for (int i = 0; i < widget.action_button_title_length; i ++) {
					mowi_set_pixel(widget.x+i, widget.y, widget.action_button_title[i], default_pop_color);
					renderer_set_pixel(widget.x+i, widget.y);
				}
			}
			else {
				for (int i = 0; i < widget.action_button_title_length; i ++) {
					mowi_set_pixel(widget.x+i, widget.y, widget.action_button_title[i], default_fg_color);
					renderer_set_pixel(widget.x+i, widget.y);
				}
			}
			break;
		}
		case MOWI_TOGGLE_BUTTON: {
			if (screen_x >= widget.x && screen_x < widget.x+widget.toggle_button_title_length && screen_y == widget.y) {
				for (int i = 0; i < widget.toggle_button_title_length; i ++) {
					mowi_set_pixel(widget.x+i, widget.y, widget.toggle_button_title[i], default_pop_color);
					renderer_set_pixel(widget.x+i, widget.y);
				}
			}
			else {
				Color color = default_fg_color;
				if (widget.toggle_button_state == 1) color = default_pop_color;
				for (int i = 0; i <  widget.toggle_button_title_length; i ++) {
					mowi_set_pixel(widget.x+i, widget.y, widget.toggle_button_title[i], color);
					renderer_set_pixel(widget.x+i, widget.y);

				}
			}
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
	#include <gl/gl.h>

	void renderer_render_screen(void) {

		for (int i = 0; i < widgets_length; i++) {
			renderer_render_widget(widgets[i]);
		}

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

		SelectObject(hdc, oldFont);
		EndPaint(window_handle, &ps);

	}

	void renderer_set_pixel(int x, int y) {

		HDC hdc = GetDC(window_handle);  // Use GetDC instead of BeginPaint

		if (h_font == NULL) {
            h_font = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Consolas");
        }
		HFONT oldFont = (HFONT)SelectObject(hdc, h_font);

		SetBkMode(hdc, OPAQUE);
    	SetBkColor(hdc, RGB(0, 0, 0));  // Black background

		SetTextColor(hdc, RGB(screen_grid[y][x].color.red, screen_grid[y][x].color.green, screen_grid[y][x].color.blue));
		char ch[2] = { screen_grid[y][x].symbol, '\0' };

		SIZE text_size;
		GetTextExtentPoint32(hdc, ch, 1, &text_size);

		TextOut(hdc, x * text_size.cx, y * text_size.cy, ch, 1);  // Correct positioning

		SelectObject(hdc, oldFont);
		ReleaseDC(window_handle, hdc);  // Release the HDC after use
	}

#endif


#ifdef __APPLE__

void renderer_render_screen(void) {

}

void renderer_set_pixel(int x, int y) {

}

#endif