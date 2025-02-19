#ifndef HALF_RECT_H_
#define HALF_RECT_H_

#include "mowi/widget.h"

void widget_input_half_rect(MowiWidget *widget);
void widget_render_half_rect(MowiWidget widget);
void widget_hover_half_rect(MowiWidget widget);

void widget_update_user_half_rect(MowiWidget widget);

void widget_create_half_rect(ToggleButton *toggle, int x, int y, char title[]);

#endif
