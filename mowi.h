#ifndef MOWI_H_
#define MOWI_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <gl/gl.h>

#pragma comment(lib, "Comctl32.lib")


/* file structure

0. DEFINITIONS
    0.1 COMMON
    0.2 MOWI
1. MAIN
2. WINDOW
3. RENDERER
4. INPUT
5. WIDGET MAIN
6. ALL WIDGETS
    6.1 TEXT
    6.2 RECT
    6.3 HALF-RECT
    6.4 ACTION BUTTON
    6.5 TOGGLE BUTTON
    6.6 LIST BOX
    6.7 RADIAL BOX
    6.8 SLIDER
    6.9 TEXT BOX

*/


/*  0. DEFINITIONS  */
#define SCREEN_COLUMNS 111
#define SCREEN_ROWS 36


// 0.1.1 COMMON - PRINT
const char PRINT_WARNING[] = "[\033[0;33mwarning\033[0m]:";
const char PRINT_ERROR[]   = "[\033[0;31merror\033[0m]:";
const char PRINT_DEBUG[]   = "[\033[0;35mdebug\033[0m]:";
const char PRINT_DONE[]    = "[\033[0;32mdone\033[0m]:";


//  0.1.2 COMMON - COLOR
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

const Color WHITE       = { 255, 255, 255 };
const Color FADED_WHITE = { 70,  70,  70  };
const Color BLACK       = { 0,   0,   0   };
const Color FADED_BLACK = { 30,  30,  30  };
const Color RED         = { 255, 30,  30  };
const Color FADED_RED   = { 70,  0,   0,  };
const Color GREEN       = { 30,  255, 30  };
const Color FADED_GREEN = { 0,   70,  70  };
const Color BLUE        = { 100, 100, 255 };
const Color FADED_BLUE  = { 0,   0,   70  };

Color default_fg_color;
Color default_fg_faded_color;
Color default_bg_color;
Color default_bg_faded_color;
Color default_pop_color;
Color default_pop_faded_color;


//  0.2.1 MOWI - MAIN
typedef struct {
    char symbol;
    Color color;
} MowiPixel;

MowiPixel screen_grid[SCREEN_ROWS][SCREEN_COLUMNS];


//  0.2.2 MOWI - WINDOW
const uint32_t WINDOW_WIDTH = 1024;
const uint32_t WINDOW_HEIGHT = 768;
static bool windiw_quit = false;
HWND window_handle;
HFONT h_font = NULL; // initialized later

int WINAPI window_RunWindow(HINSTANCE hInstance, int nCmdShow, char window_title[]);



//  0.2.3 MOWI - RENDERER
void renderer_render_screen(void);
void renderer_set_pixel(int x, int y);



//  0.2.4 MOWI - INPUT 
int screen_x = 0;
int screen_y = 0;
void input_keyboard_press(uint32_t key_code, LPARAM lParam);
void input_mouse_lmb_click(int x, int y);
void input_mouse_rmb_click(int x, int y);
void input_mouse_move(int x, int y);


//  0.2.5 MOWI - WIDGET MAIN
#define MAX_WIDGET_TITLE_LENGTH   64
#define MAX_BOX_OPTIONS           32
#define MAX_BOX_OPTION_LENGTH     64
#define MAX_USER_WIDGETS_PER_TYPE 32
#define MAX_WIDGETS               32

typedef enum {
    NONE,
    MOWI_TEXT,
    MOWI_RECT,
    MOWI_HALF_RECT,
    MOWI_ACTION_BUTTON,
    MOWI_TOGGLE_BUTTON,
    MOWI_LIST_BOX,          
    MOWI_RADIAL_BOX,   
    MOWI_SLIDER,       
    MOWI_TEXT_BOX,     
    MOWI_CONSOLE       
} WidgetType;

typedef struct {
    char title[64];
    uint16_t title_length;
    uint16_t index;
    bool is_selected;
} BoxOption;

typedef struct {

    WidgetType type;
    int index;
    int user_widget_index;
    int x;
    int y;

    // Text
    uint16_t text_length;
    char     text[255];

    // Rect
    uint16_t rect_width;
    uint16_t rect_height;

    // Half Rect
    uint16_t half_rect_width;
    uint16_t half_rect_height;


    // Action Button
    char     action_button_title[MAX_WIDGET_TITLE_LENGTH];
    uint16_t action_button_title_length;
    void   (*action_button_on_click)();

    // Toggle Button
    char     toggle_button_title[MAX_WIDGET_TITLE_LENGTH];
    uint16_t toggle_button_title_length;
    uint16_t toggle_button_state;

    // List Box
    uint16_t  list_box_length;
    uint16_t  list_box_number_of_selections;
    bool      list_box_show_counter;
    char      list_box_title[MAX_WIDGET_TITLE_LENGTH];
    char      list_box_all_options[MAX_BOX_OPTIONS][MAX_BOX_OPTION_LENGTH];
    char      list_box_selected_options[MAX_BOX_OPTIONS][MAX_BOX_OPTION_LENGTH];
    BoxOption list_box_options_internal[MAX_BOX_OPTIONS];

    // Radial Box
    uint16_t  radial_box_length;
    uint16_t  radial_box_selected_option_index;
    bool      radial_box_show_selected_index;
    char      radial_box_title[MAX_WIDGET_TITLE_LENGTH];
    char      radial_box_all_options[MAX_BOX_OPTIONS][MAX_BOX_OPTION_LENGTH];
    char      radial_box_selected_option[MAX_BOX_OPTION_LENGTH];
    BoxOption radial_box_options_internal[MAX_BOX_OPTIONS];
    
    // Slider
    uint16_t slider_length;
    uint16_t slider_selected_value;
    uint16_t slider_hover_value;
    char     slider_key;

    // Text Box
    uint16_t text_box_width;
    uint16_t text_box_height;
    uint16_t text_box_length;
    char     text_box_text[1024];

} MowiWidget;

typedef struct {
    char title[MAX_WIDGET_TITLE_LENGTH];
} ActionButton;

typedef struct {
    char title[MAX_WIDGET_TITLE_LENGTH];
    uint16_t state;
} ToggleButton;

typedef struct {
    char title[MAX_WIDGET_TITLE_LENGTH];
    int number_of_selections;
    char list_box_selected_options[MAX_BOX_OPTIONS][MAX_BOX_OPTION_LENGTH];
} ListBox;

typedef struct {
    char title[MAX_WIDGET_TITLE_LENGTH];
    int selected_index;
    char radial_box_selected_option[MAX_BOX_OPTION_LENGTH];
} RadialBox;

typedef struct {
    char title[MAX_WIDGET_TITLE_LENGTH];
    int slider_selected_value;
} Slider;

void input_click_widget_internal(MowiWidget *widget);
void renderer_render_widget(MowiWidget widget);
void renderer_hover_widget_internal(MowiWidget widget);
void widget_user_update_internal(MowiWidget widget);


ActionButton *action_buttons[MAX_USER_WIDGETS_PER_TYPE] = {NULL};
ToggleButton *toggle_buttons[MAX_USER_WIDGETS_PER_TYPE] = {NULL};
ListBox      *list_boxes[MAX_USER_WIDGETS_PER_TYPE]     = {NULL};
RadialBox    *radial_boxes[MAX_USER_WIDGETS_PER_TYPE]   = {NULL};
Slider       *sliders[MAX_USER_WIDGETS_PER_TYPE]        = {NULL};

MowiWidget widgets[MAX_WIDGETS];
uint16_t   widgets_length = 0;


//  0.2.6 MOWI - ALL WIDGETS
//  0.2.6.1 TEXT
void widget_input_text(MowiWidget *widget);
void widget_render_text(MowiWidget widget);
void widget_hover_text(MowiWidget widget);
void widget_update_user(MowiWidget widget);
void widget_create_text(ToggleButton *toggle_button, int x, int y, char title[]);

//  0.2.6.2 RECT
void widget_input_rect(MowiWidget *widget);
void widget_render_rect(MowiWidget widget);
void widget_hover_rect(MowiWidget widget);
void widget_update_user_rect(MowiWidget widget);
void widget_create_rect(ToggleButton *toggle_button, int x, int y, char title[]);

//  0.2.6.3 HALF-RECT
void widget_input_half_rect(MowiWidget *widget);
void widget_render_half_rect(MowiWidget widget);
void widget_hover_half_rect(MowiWidget widget);
void widget_update_user_half_rect(MowiWidget widget);
void widget_create_half_rect(ToggleButton *toggle_button, int x, int y, char title[]);

//  0.2.6.4 ACTION BUTTON
void widget_input_action_button(MowiWidget *widget);
void widget_render_action_button(MowiWidget widget);
void widget_hover_action_button(MowiWidget widget);
void widget_update_user_action_button(MowiWidget widget);
void widget_create_action_button(ActionButton *action_button, int x, int y, char title[], void (*on_click_function)());

//  0.2.6.5 TOGGLE BUTTON
void widget_input_toggle_button(MowiWidget *widget);
void widget_render_toggle_button(MowiWidget widget);
void widget_hover_toggle_button(MowiWidget widget);
void widget_update_user_toggle_button(MowiWidget widget);

//  0.2.6.6 LIST BOX
void widget_input_list_box(MowiWidget *widget);
void widget_render_list_box(MowiWidget widget);
void widget_hover_list_box(MowiWidget widget);
void widget_update_user_list_box(MowiWidget widget);
void widget_create_list_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)());

//  0.2.6.7 RADIAL BOX
void widget_input_radial_box(MowiWidget *widget);
void widget_render_radial_box(MowiWidget widget);
void widget_hover_radial_box(MowiWidget widget);
void widget_update_user_radial_box(MowiWidget widget);
void widget_create_radial_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)());

//  0.2.6.8 SLIDER
void widget_input_slider(MowiWidget *widget);
void widget_render_slider(MowiWidget widget);
void widget_hover_slider(MowiWidget widget);
void widget_update_user_slider(MowiWidget widget);
void widget_create_slider(ActionButton *action, int x, int y, char title[], void (*on_click_function)());

//  0.2.6.9 TEXT BOX
void widget_input_text_box(MowiWidget *widget);
void widget_render_text_box(MowiWidget widget);
void widget_hover_text_box(MowiWidget widget);
void widget_update_user_text_box(MowiWidget widget);
void widget_create_text_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)());

/* 1. MOWI  */

void mowi_set_pixel_internal(int x, int y, char symbol, Color color) {
    screen_grid[y][x].symbol = symbol;
	screen_grid[y][x].color = color;
}

void mowi_redraw_tick_internal(void) {
    
}
void mowi_tick_internal(void) { 

}

void mowi_create(char window_title[]) {

    /*
    MowiWidget list_box = {
        .type = MOWI_LIST_BOX,
        .x = 35,
        .y = 13,
        .list_box_length = 5,
        .list_box_show_counter = true,
        .list_box_number_of_selections = 0,
        .list_box_title = "ListBox",
        .list_box_all_options = {"Option", "Alternativ", "Test", "Hejsan", "Detta"}
    };
    mowi_add_widget(list_box, 0);

    MowiWidget radial_box = {
        .type = MOWI_RADIAL_BOX,
        .x = 55,
        .y = 13,
        .radial_box_length = 5,
        .radial_box_show_selected_index = true,
        .radial_box_title = "RadialBox",
        .radial_box_all_options = {"Option", "Alternativ", "Test", "Hejsan", "Detta"}
    };
    mowi_add_widget(radial_box, 0);
    */

    default_fg_color        = WHITE;
    default_fg_faded_color  = FADED_WHITE;
    default_bg_color        = BLACK;
    default_bg_faded_color  = FADED_BLACK;
    default_pop_color       = GREEN;
    default_pop_faded_color = FADED_GREEN;

    for (int y = 0; y < SCREEN_ROWS; y++) {
        for (int x = 0; x < SCREEN_COLUMNS; x++) {
            mowi_set_pixel_internal(x, y, ' ', FADED_WHITE);
        }
    }

    #ifdef _WIN32
        HINSTANCE hInstance = GetModuleHandle(NULL);
        window_RunWindow(hInstance, SW_SHOWDEFAULT, window_title);
    #endif


    #ifdef __APPLE__
        printf("%s mowi does not work on MacOS yet.\n", PRINT_WARNING);
    #endif


}



/* 2. WINDOW  */

// Custom Paint for Edit Control
LRESULT CALLBACK SubclassEditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
    switch (message) {

        case WM_PAINT: {
            renderer_render_screen();
            mowi_redraw_tick_internal();
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
int WINAPI window_RunWindow(HINSTANCE hInstance, int nCmdShow, char window_title[]) {

    static WNDCLASS window_class = { 0 };
    static const wchar_t window_class_name[] = L"My Window Class";
    window_class.lpszClassName = (PCSTR)window_class_name;
    window_class.lpfnWndProc = WindowsProcessMessage;
    window_class.hInstance = hInstance;

    RegisterClass(&window_class);

    window_handle =
        CreateWindow((PCSTR)window_class_name, window_title, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
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

    while (!windiw_quit) {
        static MSG message = { 0 };
        while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        mowi_tick_internal();

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
            windiw_quit = true;
        } break;	

        default: { // message not handled; pass on to default message handling function
            return DefWindowProc(window_handle, message, wParam, lParam);
        } break;
    }
    return 0;
}






/*  3. RENDERER  */

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





/*  4. INPUT  */



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

void input_mouse_lmb_click(int x, int y) {
    screen_x = x / 9;
    screen_y = y / 20;
    for (int i = 0; i < widgets_length; i++) {
        input_click_widget_internal(&widgets[i]);
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
            renderer_hover_widget_internal(widgets[i]);
        }
    }
}

void mowi_add_widget(MowiWidget widget, int user_widget_index) {
    for (int i = 0; i < MAX_WIDGETS; i++) {
        if (widgets[i].type == NONE) {
            widgets[i] = widget;
            widgets[i].index = i;
            widgets[i].user_widget_index = user_widget_index;
            widgets_length++;
            switch (widgets[i].type) {
                case MOWI_LIST_BOX: {
                    for (int j = 0; j < widgets[i].list_box_length; j++) {
                        BoxOption option = { .index = j, .is_selected = false, .title_length=strlen(widgets[i].list_box_all_options[j]) };
                        strcpy(option.title, widgets[i].list_box_all_options[j]);
                        widgets[i].list_box_options_internal[j] = option;   
                    }
                    break;
                }
                case MOWI_RADIAL_BOX: {
                    for (int j = 0; j < widgets[i].radial_box_length; j++) {
                        BoxOption option = { .index = j, .is_selected = false, .title_length=strlen(widgets[i].radial_box_all_options[j]) };
                        strcpy(option.title, widgets[i].radial_box_all_options[j]);
                        widgets[i].radial_box_options_internal[j] = option;   
                    }
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
            break;
        }
    }
}




/*  5. WIDGET - MAIN  */
void input_click_widget_internal(MowiWidget *widget) {
	switch (widget->type) {
		case MOWI_TEXT:          { break; }
		case MOWI_RECT:          { break; }
		case MOWI_HALF_RECT:     { break; }
		case MOWI_ACTION_BUTTON: { widget_input_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_input_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_input_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_input_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_input_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_input_text_box(widget); break; }
	}
}

void renderer_render_widget(MowiWidget widget) {
	switch (widget.type) {
		case MOWI_TEXT: 		 { widget_render_text(widget); break; }
		case MOWI_RECT: 		 { widget_render_rect(widget); break; }
		case MOWI_HALF_RECT: 	 { widget_render_half_rect(widget); break; }
		case MOWI_ACTION_BUTTON: { widget_render_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_render_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_render_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_render_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_render_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_render_text_box(widget); break; }
	}
}

void renderer_hover_widget_internal(MowiWidget widget) {
	switch (widget.type) {
		case MOWI_TEXT:          { break; }
		case MOWI_RECT:          { break; }
		case MOWI_HALF_RECT:     { break; }
		case MOWI_ACTION_BUTTON: { widget_hover_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_hover_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_hover_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_hover_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_hover_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_hover_text_box(widget); break; }
	}
}

/* Updates the structs that the user uses to create widgets. */
void widget_user_update_internal(MowiWidget widget) {
    switch (widget.type) {
		case MOWI_ACTION_BUTTON: { widget_update_user_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_update_user_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_update_user_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_update_user_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_update_user_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_update_user_text_box(widget); break; }
	}
}






/*  6 ALL WIDGETS  */

/*  6.1 TEXT  */
void widget_input_text(MowiWidget *widget) {

}

void widget_render_text(MowiWidget widget) {
    for (int i = 0; i < widget.text_length; i ++) {
        mowi_set_pixel_internal(widget.x+i, widget.y, widget.text[i], default_fg_color);
    }
}

void widget_hover_text(MowiWidget widget) {
    
}

void widget_update_user(MowiWidget widget) {

}

void widget_create_text(ToggleButton *toggle_button, int x, int y, char title[]) {
    MowiWidget widget = {.type = MOWI_TOGGLE_BUTTON, .x = x, .y = y, .toggle_button_state = 0, .toggle_button_title_length=strlen(title)};
    toggle_button->state = widget.toggle_button_state;
    strcpy(widget.toggle_button_title, title);

    int i = 0;
    while (i < 32) {
        if (toggle_buttons[i] == NULL) {
            toggle_buttons[i] = toggle_button;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.2 RECT  */
void widget_input_rect(MowiWidget *widget) {

}

void widget_render_rect(MowiWidget widget) {
    mowi_set_pixel_internal(widget.x, 				   widget.y, 					    '.', default_fg_color);
    mowi_set_pixel_internal(widget.x+widget.rect_width-1, widget.y,					    '.', default_fg_color);
    mowi_set_pixel_internal(widget.x, 				   widget.y+widget.rect_height-1,   '\'', default_fg_color);
    mowi_set_pixel_internal(widget.x+widget.rect_width-1, widget.y+widget.rect_height-1, '\'', default_fg_color);

    for (int i = 1; i < widget.rect_width-1; i++) {
        mowi_set_pixel_internal(widget.x+i, widget.y, 					  '-', default_fg_color);
        mowi_set_pixel_internal(widget.x+i, widget.y+widget.rect_height-1, '-', default_fg_color);
    }
    for (int i = 1; i < widget.rect_height-1; i++) {
        mowi_set_pixel_internal(widget.x, widget.y+i, 					  '|', default_fg_color);
        mowi_set_pixel_internal(widget.x+widget.rect_width-1, widget.y+i,  '|', default_fg_color);
    }
}

void widget_hover_rect(MowiWidget widget) {

}

void widget_update_user_rect(MowiWidget widget) {

}

void widget_create_rect(ToggleButton *toggle_button, int x, int y, char title[]) {
    MowiWidget widget = {.type = MOWI_TOGGLE_BUTTON, .x = x, .y = y, .toggle_button_state = 0, .toggle_button_title_length=strlen(title)};
    toggle_button->state = widget.toggle_button_state;
    strcpy(widget.toggle_button_title, title);

    int i = 0;
    while (i < 32) {
        if (toggle_buttons[i] == NULL) {
            toggle_buttons[i] = toggle_button;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.3 HALF-RECT  */
void widget_input_half_rect(MowiWidget *widget) {

}

void widget_render_half_rect(MowiWidget widget) {
    mowi_set_pixel_internal(widget.x, 				  		  widget.y, 					      '.', default_fg_color);
    mowi_set_pixel_internal(widget.x+widget.half_rect_width-1, widget.y,					          '.', default_fg_color);
    mowi_set_pixel_internal(widget.x, 				          widget.y+widget.half_rect_height-1, '\'', default_fg_color);
    mowi_set_pixel_internal(widget.x+widget.half_rect_width-1, widget.y+widget.half_rect_height-1, '\'', default_fg_color);

    for (int i = 1; i < widget.half_rect_width-1; i++) {
        mowi_set_pixel_internal(widget.x+i, widget.y, 				           '-', default_fg_color);
        mowi_set_pixel_internal(widget.x+i, widget.y+widget.half_rect_height-1, '-', default_fg_color);
    }
    for (int i = 1; i < widget.half_rect_height-1; i++) {
        mowi_set_pixel_internal(widget.x, widget.y+i, 					  '|', default_fg_color);
    }
}

void widget_hover_half_rect(MowiWidget widget) {

}

void widget_update_user_half_rect(MowiWidget widget) {

}

void widget_create_half_rect(ToggleButton *toggle_button, int x, int y, char title[]) {
    MowiWidget widget = {.type = MOWI_TOGGLE_BUTTON, .x = x, .y = y, .toggle_button_state = 0, .toggle_button_title_length=strlen(title)};
    toggle_button->state = widget.toggle_button_state;
    strcpy(widget.toggle_button_title, title);

    int i = 0;
    while (i < 32) {
        if (toggle_buttons[i] == NULL) {
            toggle_buttons[i] = toggle_button;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.4 ACTION BUTTON  */
void widget_input_action_button(MowiWidget *widget) {
    if (screen_x >= widget->x && screen_x < widget->x+widget->action_button_title_length && screen_y == widget->y) {
        widget->action_button_on_click();
    }
}

void widget_render_action_button(MowiWidget widget) {
    for (int i = 0; i < widget.action_button_title_length; i ++) { // same as mowi_text :/
        mowi_set_pixel_internal(widget.x+i, widget.y, widget.action_button_title[i], default_fg_color);
    }
}

void widget_hover_action_button(MowiWidget widget) {
    if (screen_x >= widget.x && screen_x < widget.x+widget.action_button_title_length && screen_y == widget.y) {
        for (int i = 0; i < widget.action_button_title_length; i ++) {
            mowi_set_pixel_internal(widget.x+i, widget.y, widget.action_button_title[i], default_pop_color);
            renderer_set_pixel(widget.x+i, widget.y);
        }
    }
    else {
        for (int i = 0; i < widget.action_button_title_length; i ++) {
            
            mowi_set_pixel_internal(widget.x+i, widget.y, widget.action_button_title[i], default_fg_color);
            renderer_set_pixel(widget.x+i, widget.y);
        }
    }
}

void widget_update_user_action_button(MowiWidget widget) {

}

void widget_create_action_button(ActionButton *action_button, int x, int y, char title[], void (*on_click_function)()) {
    MowiWidget widget = {.type = MOWI_ACTION_BUTTON, .x = x, .y = y, .action_button_title_length=strlen(title), .action_button_on_click = on_click_function};
    strcpy(widget.action_button_title, title);

    int i = 0;
    while (i < 32) {
        if (action_buttons[i] == NULL) {
            action_buttons[i] = action_button;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.5 TOGGLE BUTTON  */
void widget_input_toggle_button(MowiWidget *widget) {
    if (screen_x >= widget->x && screen_x < widget->x+widget->toggle_button_title_length+4 && screen_y == widget->y) {
        if (widget->toggle_button_state == 0) {
            widget->toggle_button_state = 1;
            mowi_set_pixel_internal(widget->x+1, widget->y, '+', default_pop_color);
            renderer_set_pixel(widget->x+1, widget->y);
        }
        else if (widget->toggle_button_state == 1) {
            widget->toggle_button_state = 0;
            mowi_set_pixel_internal(widget->x+1, widget->y, ' ', default_fg_color);
            renderer_set_pixel(widget->x+1, widget->y);
        }
        widget_user_update_internal(*widget);
    }
}

void widget_render_toggle_button(MowiWidget widget) {
    mowi_set_pixel_internal(widget.x,   widget.y, '[', default_fg_color);
    mowi_set_pixel_internal(widget.x+1, widget.y, '-', default_fg_color);
    mowi_set_pixel_internal(widget.x+2, widget.y, ']', default_fg_color);
    Color color = default_fg_color;
    if (widget.toggle_button_state == 1) {
        color = default_pop_color;
        mowi_set_pixel_internal(widget.x+1, widget.y, '+', default_pop_color);
    }
    for (int i = 0; i <  widget.toggle_button_title_length; i ++) { // same as mowi_text :/
        mowi_set_pixel_internal(widget.x+4+i, widget.y, widget.toggle_button_title[i], color);
    }
}

void widget_hover_toggle_button(MowiWidget widget) {
    if (screen_x >= widget.x && screen_x < widget.x+widget.toggle_button_title_length+4 && screen_y == widget.y) {
        for (int i = 0; i < widget.toggle_button_title_length; i ++) {
            mowi_set_pixel_internal(widget.x+4+i, widget.y, widget.toggle_button_title[i], default_pop_color);
            renderer_set_pixel(widget.x+4+i, widget.y);
        }
    }
    else {
        Color color = default_fg_color;
        if (widget.toggle_button_state == 1) color = default_pop_color;
        for (int i = 0; i <  widget.toggle_button_title_length; i ++) {
            mowi_set_pixel_internal(widget.x+4+i, widget.y, widget.toggle_button_title[i], color);
            renderer_set_pixel(widget.x+4+i, widget.y);

        }
    }
}

void widget_update_user_toggle_button(MowiWidget widget) {
    toggle_buttons[widget.user_widget_index]->state = widget.toggle_button_state;
}

void widget_create_toggle_button(ToggleButton *toggle_button, int x, int y, char title[]) {
    MowiWidget widget = {.type = MOWI_TOGGLE_BUTTON, .x = x, .y = y, .toggle_button_state = 0, .toggle_button_title_length=strlen(title)};
    toggle_button->state = widget.toggle_button_state;
    strcpy(widget.toggle_button_title, title);

    int i = 0;
    while (i < 32) {
        if (toggle_buttons[i] == NULL) {
            toggle_buttons[i] = toggle_button;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.6 LIST BOX  */
void widget_input_list_box(MowiWidget *widget) {
    for (int i = 0; i < widget->list_box_length; i++) {
        if (screen_x >= widget->x+1 && screen_x < widget->x+2+widget->list_box_options_internal[i].title_length && screen_y == widget->y+1+widget->list_box_options_internal[i].index) {
            if (widget->list_box_options_internal[i].is_selected == false) {
                mowi_set_pixel_internal(widget->x+1, widget->y+1+i, '+', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->list_box_options_internal[i].is_selected = true;
            }
            else {
                mowi_set_pixel_internal(widget->x+1, widget->y+1+i, ' ', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->list_box_options_internal[i].is_selected = false;

            }
        }
    }
}

void widget_render_list_box(MowiWidget widget) {
    MowiWidget half_rect = {.type = MOWI_HALF_RECT, .x = widget.x, .y = widget.y, .half_rect_width = 3, .half_rect_height = widget.list_box_length+2};
    renderer_render_widget(half_rect);

    // title
    mowi_set_pixel_internal(widget.x+2, widget.y, '[', default_fg_color);
    for (int i = 0; i < strlen(widget.list_box_title); i ++) {
        mowi_set_pixel_internal(widget.x+3+i, widget.y, widget.list_box_title[i], default_fg_color);
    }
    mowi_set_pixel_internal(widget.x+3+strlen(widget.list_box_title), widget.y, ']', default_fg_color);
    
    // options
    for (int i = 0; i < widget.list_box_length; i ++) {
        if (widget.list_box_options_internal[i].is_selected == 1) {
            mowi_set_pixel_internal(widget.x+1, widget.y+1+i, '+', default_pop_color);
        }
        else {
            mowi_set_pixel_internal(widget.x+1, widget.y+1+i, ' ', default_fg_color);
        }
        for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
            mowi_set_pixel_internal(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
        }
    }
    if (widget.list_box_show_counter == true) {
        // TODO: 
    }
}

void widget_hover_list_box(MowiWidget widget) {
    for (int i = 0; i < widget.list_box_length; i++) {
        if (screen_x >= widget.x+1 && screen_x < widget.x+2+widget.list_box_options_internal[i].title_length && screen_y == widget.y+1+widget.list_box_options_internal[i].index) {
            for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
                mowi_set_pixel_internal(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_pop_color);
                renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

            }
        } 
        else {
            for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
                mowi_set_pixel_internal(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
                renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

            }
        }
    }
}

void widget_update_user_list_box(MowiWidget widget) {

}

void widget_create_list_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)()) {
    MowiWidget widget = {.type = MOWI_ACTION_BUTTON, .x = x, .y = y, .action_button_title_length=strlen(title), .action_button_on_click = on_click_function};
    strcpy(widget.action_button_title, title);

    int i = 0;
    while (i < 32) {
        if (action_buttons[i] == NULL) {
            action_buttons[i] = action;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.7 RADIAL BOX  */
void widget_input_radial_box(MowiWidget *widget) {
    for (int i = 0; i < widget->radial_box_length; i++) {
        if (screen_x >= widget->x+1 && screen_x < widget->x+2+widget->radial_box_options_internal[i].title_length && screen_y == widget->y+1+widget->radial_box_options_internal[i].index) {
            if (widget->radial_box_options_internal[i].is_selected == false) {
                mowi_set_pixel_internal(widget->x+1, widget->y+1+i, '>', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->radial_box_options_internal[i].is_selected = true;
                for (int j = 0; j < widget->radial_box_length; j++) {
                    if (j==i) continue;
                    widget->radial_box_options_internal[j].is_selected = false;
                }
                renderer_hover_widget_internal(*widget);
            }
            else {
                mowi_set_pixel_internal(widget->x+1, widget->y+1+i, ' ', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->radial_box_options_internal[i].is_selected = false;

            }
        }
    }
}

void widget_render_radial_box(MowiWidget widget) {
    MowiWidget half_rect = {.type = MOWI_HALF_RECT, .x = widget.x, .y = widget.y, .half_rect_width = 3, .half_rect_height = widget.radial_box_length+2};
    renderer_render_widget(half_rect);

    // title
    mowi_set_pixel_internal(widget.x+2, widget.y, '[', default_fg_color);
    for (int i = 0; i < strlen(widget.radial_box_title); i ++) {
        mowi_set_pixel_internal(widget.x+3+i, widget.y, widget.radial_box_title[i], default_fg_color);
    }
    mowi_set_pixel_internal(widget.x+3+strlen(widget.radial_box_title), widget.y, ']', default_fg_color);

    // options
    for (int i = 0; i < widget.radial_box_length; i ++) {
        if (widget.radial_box_options_internal[i].is_selected == 1) {
            mowi_set_pixel_internal(widget.x+1, widget.y+1+i, '>', default_pop_color);
        }
        else {
            mowi_set_pixel_internal(widget.x+1, widget.y+1+i, ' ', default_fg_color);
        }
        for (int j = 0; j < widget.radial_box_options_internal[i].title_length; j++) {
            mowi_set_pixel_internal(widget.x + 2 + j, widget.y + 1 + i, widget.radial_box_options_internal[i].title[j], default_fg_color);
        }
    }
}

void widget_hover_radial_box(MowiWidget widget) {
    for (int i = 0; i < widget.radial_box_length; i++) {
        if (screen_x >= widget.x+1 && screen_x < widget.x+2+widget.radial_box_options_internal[i].title_length && screen_y == widget.y+1+widget.radial_box_options_internal[i].index) {
            if (widget.radial_box_options_internal[i].is_selected == true) {
                mowi_set_pixel_internal(widget.x+1, widget.y+1+i, '>', default_pop_color);
                renderer_set_pixel(widget.x+1, widget.y+1+i);
            }
            renderer_set_pixel(widget.x+1, widget.y+1+i);
            for (int j = 0; j < widget.radial_box_options_internal[i].title_length; j++) {
                mowi_set_pixel_internal(widget.x + 2 + j, widget.y + 1 + i, widget.radial_box_options_internal[i].title[j], default_pop_color);
                renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

            }
        } 
        else {
            if (widget.radial_box_options_internal[i].is_selected == true) {
                mowi_set_pixel_internal(widget.x+1, widget.y+1+i, '-', default_fg_color);
                renderer_set_pixel(widget.x+1, widget.y+1+i);
            }
            else {
                mowi_set_pixel_internal(widget.x+1, widget.y+1+i, ' ', default_fg_color);
                renderer_set_pixel(widget.x+1, widget.y+1+i);
            }
            for (int j = 0; j < widget.radial_box_options_internal[i].title_length; j++) {
                mowi_set_pixel_internal(widget.x + 2 + j, widget.y + 1 + i, widget.radial_box_options_internal[i].title[j], default_fg_color);
                renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

            }
        }
    }
}

void widget_update_user_radial_box(MowiWidget widget) {

}

void widget_create_radial_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)()) {
    MowiWidget widget = {.type = MOWI_ACTION_BUTTON, .x = x, .y = y, .action_button_title_length=strlen(title), .action_button_on_click = on_click_function};
    strcpy(widget.action_button_title, title);

    int i = 0;
    while (i < 32) {
        if (action_buttons[i] == NULL) {
            action_buttons[i] = action;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.8 SLIDER  */
void widget_input_slider(MowiWidget *widget) {

}

void widget_render_slider(MowiWidget widget) {

}

void widget_hover_slider(MowiWidget widget) {

}

void widget_update_user_slider(MowiWidget widget) {

}

void widget_create_slider(ActionButton *action, int x, int y, char title[], void (*on_click_function)()) {
    MowiWidget widget = {.type = MOWI_ACTION_BUTTON, .x = x, .y = y, .action_button_title_length=strlen(title), .action_button_on_click = on_click_function};
    strcpy(widget.action_button_title, title);

    int i = 0;
    while (i < 32) {
        if (action_buttons[i] == NULL) {
            action_buttons[i] = action;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}


/*  6.8 TEXT BOX  */
void widget_input_text_box(MowiWidget *widget) {

}

void widget_render_text_box(MowiWidget widget) {

}

void widget_hover_text_box(MowiWidget widget) {

}

void widget_update_user_text_box(MowiWidget widget) {

}

void widget_create_text_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)()) {
    MowiWidget widget = {.type = MOWI_ACTION_BUTTON, .x = x, .y = y, .action_button_title_length=strlen(title), .action_button_on_click = on_click_function};
    strcpy(widget.action_button_title, title);

    int i = 0;
    while (i < 32) {
        if (action_buttons[i] == NULL) {
            action_buttons[i] = action;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}



#endif // MOWI_H_
