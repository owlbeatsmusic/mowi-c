
#include "common/color.h"

#include "mowi/widget/widget.h"
#include "mowi/input.h"

void widget_input_list_box(MowiWidget *widget) {
    for (int i = 0; i < widget->list_box_length; i++) {
        if (screen_x >= widget->x+1 && screen_x < widget->x+2+widget->list_box_options_internal[i].title_length && screen_y == widget->y+1+widget->list_box_options_internal[i].index) {
            if (widget->list_box_options_internal[i].is_selected == false) {
                mowi_set_pixel(widget->x+1, widget->y+1+i, '+', default_pop_color);
                renderer_set_pixel(widget->x+1, widget->y+1+i);
                widget->list_box_options_internal[i].is_selected = true;
            }
            else {
                mowi_set_pixel(widget->x+1, widget->y+1+i, ' ', default_pop_color);
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
    mowi_set_pixel(widget.x+2, widget.y, '[', default_fg_color);
    for (int i = 0; i < strlen(widget.list_box_title); i ++) {
        mowi_set_pixel(widget.x+3+i, widget.y, widget.list_box_title[i], default_fg_color);
    }
    mowi_set_pixel(widget.x+3+strlen(widget.list_box_title), widget.y, ']', default_fg_color);
    
    // options
    for (int i = 0; i < widget.list_box_length; i ++) {
        if (widget.list_box_options_internal[i].is_selected == 1) {
            mowi_set_pixel(widget.x+1, widget.y+1+i, '+', default_pop_color);
        }
        else {
            mowi_set_pixel(widget.x+1, widget.y+1+i, ' ', default_fg_color);
        }
        for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
            mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
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
                mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_pop_color);
                renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

            }
        } 
        else {
            for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
                mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
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