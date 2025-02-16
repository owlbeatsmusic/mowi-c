#include <stdint.h>

typedef enum {      // status:
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
    uint8_t is_selected;
} BoxOption;

typedef struct {

    WidgetType type;

    int x;
    int y;

    //void (*render_fptr)();
    //void (*hover_fptr)();
    //void (*click_fptr)();


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
    char     action_button_title[64];
    uint16_t action_button_title_length;
    void   (*action_button_on_click)();

    // Toggle Button
    char     toggle_button_title[64];
    uint16_t toggle_button_title_length;
    uint16_t toggle_button_state;

    // List Box
    uint16_t  list_box_length;
    uint16_t  list_box_selected_options_count;
    char      list_box_title[64];
    char      list_box_all_options[32][64];
    char      list_box_selected_options[32][64];
    BoxOption list_box_options_internal[64];

    // Radial Box
    uint16_t  radial_box_length;
    uint16_t  radial_box_selected_option_index;
    char      radial_box_title[64];
    char      radial_box_all_options[32][64];
    char      radial_box_selected_option[64];
    BoxOption radial_box_options_internal[64];
    
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

} Widget;

extern Widget   widgets[64];
extern uint16_t widgets_length;
