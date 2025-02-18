#ifndef WIDGET_H_
#define WIDGET_H_

#include <stdint.h>
#include <stdbool.h>

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
    char     action_button_title[64];
    uint16_t action_button_title_length;
    void   (*action_button_on_click)();

    // Toggle Button
    char     toggle_button_title[64];
    uint16_t toggle_button_title_length;
    uint16_t toggle_button_state;

    // List Box
    uint16_t  list_box_length;
    uint16_t  list_box_number_of_selections;
    bool      list_box_show_counter;
    char      list_box_title[64];
    char      list_box_all_options[32][64];
    char      list_box_selected_options[32][64];
    BoxOption list_box_options_internal[64];

    // Radial Box
    uint16_t  radial_box_length;
    uint16_t  radial_box_selected_option_index;
    bool      radial_box_show_selected_index;
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

} MowiWidget;

typedef struct {
    char title[64];
} ActionButton;

typedef struct {
    char title[64];
    uint16_t state;
} ToggleButton;

typedef struct {
    char title[64];
    int number_of_selections;
    char list_box_selected_options[32][64];
} ListBox;

typedef struct {
    char title[64];
    int selected_index;
    char radial_box_selected_option[64];
} RadialBox;

typedef struct {
    char title[64];
    int slider_selected_value;
} Slider;

extern ActionButton *action_buttons[32];
extern ToggleButton *toggle_buttons[32];
extern ListBox      *list_boxes[32];
extern RadialBox    *radial_boxes[32];
extern Slider       *sliders[32];

extern MowiWidget widgets[64];
extern uint16_t   widgets_length;

extern void mowi_add_widget(MowiWidget widget, int user_widget_index);
extern void widget_user_update(MowiWidget widget);

#endif
