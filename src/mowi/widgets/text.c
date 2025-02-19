
#include "common/color.h"

#include "mowi/widget.h"
#include "mowi/input.h"

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
