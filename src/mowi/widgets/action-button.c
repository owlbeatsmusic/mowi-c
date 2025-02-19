
#include "common/color.h"

#include "mowi/widget.h"
#include "mowi/input.h"

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