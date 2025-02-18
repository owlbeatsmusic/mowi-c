
#include "common/color.h"

#include "mowi/widget/widget.h"
#include "mowi/input.h"

void widget_input_half_rect(MowiWidget *widget) {

}

void widget_render_half_rect(MowiWidget widget) {
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
