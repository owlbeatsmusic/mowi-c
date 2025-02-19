#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_

#include "mowi/widget.h"

void widget_input_text_box(MowiWidget *widget);
void widget_render_text_box(MowiWidget widget);
void widget_hover_text_box(MowiWidget widget);

void widget_update_user_text_box(MowiWidget widget);

void widget_create_text_box(ActionButton *action, int x, int y, char title[], void (*on_click_function)());

#endif
