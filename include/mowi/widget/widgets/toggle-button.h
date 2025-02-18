#ifndef TOGGLE_BUTTON_H_
#define TOGGLE_BUTTON_H_

#include "mowi/widget/widget.h"

void widget_input_toggle_button(MowiWidget *widget);
void widget_render_toggle_button(MowiWidget widget);
void widget_hover_toggle_button(MowiWidget widget);

void widget_update_user_toggle_button(MowiWidget widget);

void widget_create_toggle_button(ToggleButton *toggle, int x, int y, char title[]);

#endif
