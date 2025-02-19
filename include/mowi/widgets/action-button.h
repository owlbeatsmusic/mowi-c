#ifndef ACTION_BUTTON_H_
#define ACTION_BUTTON_H_

#include "mowi/widget.h"

void widget_input_action_button(MowiWidget *widget);
void widget_render_action_button(MowiWidget widget);
void widget_hover_action_button(MowiWidget widget);

void widget_update_user_action_button(MowiWidget widget);

void widget_create_action_button(ActionButton *action_button, int x, int y, char title[], void (*on_click_function)());

#endif
