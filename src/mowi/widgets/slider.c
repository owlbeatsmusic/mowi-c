
#include "common/color.h"

#include "mowi/widget.h"
#include "mowi/input.h"

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