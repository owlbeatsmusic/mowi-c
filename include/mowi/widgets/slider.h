#ifndef SLIDER_H_
#define SLIDER_H_

#include "mowi/widget.h"

void widget_input_slider(MowiWidget *widget);
void widget_render_slider(MowiWidget widget);
void widget_hover_slider(MowiWidget widget);

void widget_update_user_slider(MowiWidget widget);

void widget_create_slider(ToggleButton *toggle, int x, int y, char title[]);

#endif
