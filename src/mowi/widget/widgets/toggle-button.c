
#include "common/color.h"

#include "mowi/widget/widget.h"
#include "mowi/input.h"

void widget_input_toggle_button(MowiWidget *widget) {
    if (screen_x >= widget->x && screen_x < widget->x+widget->toggle_button_title_length+4 && screen_y == widget->y) {
        if (widget->toggle_button_state == 0) {
            widget->toggle_button_state = 1;
            mowi_set_pixel(widget->x+1, widget->y, '+', default_pop_color);
            renderer_set_pixel(widget->x+1, widget->y);
        }
        else if (widget->toggle_button_state == 1) {
            widget->toggle_button_state = 0;
            mowi_set_pixel(widget->x+1, widget->y, ' ', default_fg_color);
            renderer_set_pixel(widget->x+1, widget->y);
        }
        widget_user_update(*widget);
    }
}

void widget_render_toggle_button(MowiWidget widget) {
    mowi_set_pixel(widget.x,   widget.y, '[', default_fg_color);
    mowi_set_pixel(widget.x+1, widget.y, '-', default_fg_color);
    mowi_set_pixel(widget.x+2, widget.y, ']', default_fg_color);
    Color color = default_fg_color;
    if (widget.toggle_button_state == 1) {
        color = default_pop_color;
        mowi_set_pixel(widget.x+1, widget.y, '+', default_pop_color);
    }
    for (int i = 0; i <  widget.toggle_button_title_length; i ++) { // same as mowi_text :/
        mowi_set_pixel(widget.x+4+i, widget.y, widget.toggle_button_title[i], color);
    }
}

void widget_hover_toggle_button(MowiWidget widget) {
    if (screen_x >= widget.x && screen_x < widget.x+widget.toggle_button_title_length+4 && screen_y == widget.y) {
        for (int i = 0; i < widget.toggle_button_title_length; i ++) {
            mowi_set_pixel(widget.x+4+i, widget.y, widget.toggle_button_title[i], default_pop_color);
            renderer_set_pixel(widget.x+4+i, widget.y);
        }
    }
    else {
        Color color = default_fg_color;
        if (widget.toggle_button_state == 1) color = default_pop_color;
        for (int i = 0; i <  widget.toggle_button_title_length; i ++) {
            mowi_set_pixel(widget.x+4+i, widget.y, widget.toggle_button_title[i], color);
            renderer_set_pixel(widget.x+4+i, widget.y);

        }
    }
}

void widget_update_user_toggle_button(MowiWidget widget) {
    toggle_buttons[widget.user_widget_index]->state = widget.toggle_button_state;
}

void widget_create_toggle_button(ToggleButton *toggle, int x, int y, char title[]) {
    MowiWidget widget = {.type = MOWI_TOGGLE_BUTTON, .x = x, .y = y, .toggle_button_state = 0, .toggle_button_title_length=strlen(title)};
    toggle->state = widget.toggle_button_state;
    strcpy(widget.toggle_button_title, title);

    int i = 0;
    while (i < 32) {
        if (toggle_buttons[i] == NULL) {
            toggle_buttons[i] = toggle;
            break;
        }
        i++;
    }
    mowi_add_widget(widget, i);
}
