#ifndef RECT_H_
#define RECT_H_

#include "mowi/widget.h"

void widget_input_rect(MowiWidget *widget);
void widget_render_rect(MowiWidget widget);
void widget_hover_rect(MowiWidget widget);

void widget_update_user_rect(MowiWidget widget);

void widget_create_rect(ToggleButton *toggle, int x, int y, char title[]);

#endif
