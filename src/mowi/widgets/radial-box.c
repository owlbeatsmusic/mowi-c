
#include "common/color.h"

#include "mowi/widget/widget.h"
#include "mowi/input.h"

void widget_input_radial_box(MowiWidget *widget) {
    for (int i = 0; i < widget->radial_box_length; i++) {
        if (screen_x >= widget->x+1 && screen_x < widget->x+2+widget->radial_box_options_internal[i].title_length && screen_y == widget->y+1+widget->radial_box_options_internal[i].index) {
            if (widget->radial_box_options_internal[i].is_selected == false) {
                mowi_set_pixel(widget->x+1, widget->y+1+i, '>', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->radial_box_options_internal[i].is_selected = true;
                for (int j = 0; j < widget->radial_box_length; j++) {
                    if (j==i) continue;
                    widget->radial_box_options_internal[j].is_selected = false;
                }
                renderer_hover_widget(*widget);
            }
            else {
                mowi_set_pixel(widget->x+1, widget->y+1+i, ' ', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->radial_box_options_internal[i].is_selected = false;

            }
        }
    }
}

void widget_render_radial_box(MowiWidget widget) {

}

void widget_hover_radial_box(MowiWidget widget) {

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