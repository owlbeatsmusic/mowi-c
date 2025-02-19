#ifndef WIDGET_H_
#define WIDGET_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_WIDGET_TITLE_LENGTH   64
#define MAX_BOX_OPTIONS           32
#define MAX_BOX_OPTION_LENGTH     64
#define MAX_USER_WIDGETS_PER_TYPE 32
#define MAX_WIDGETS               32

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

extern ActionButton *action_buttons[MAX_USER_WIDGETS_PER_TYPE];
extern ToggleButton *toggle_buttons[MAX_USER_WIDGETS_PER_TYPE];
extern ListBox      *list_boxes[MAX_USER_WIDGETS_PER_TYPE];
extern RadialBox    *radial_boxes[MAX_USER_WIDGETS_PER_TYPE];
extern Slider       *sliders[MAX_USER_WIDGETS_PER_TYPE];

extern MowiWidget widgets[MAX_WIDGETS];
extern uint16_t   widgets_length;

extern void mowi_add_widget(MowiWidget widget, int user_widget_index);
extern void widget_user_update_internal(MowiWidget widget);

#endif
