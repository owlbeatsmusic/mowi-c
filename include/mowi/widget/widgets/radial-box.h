#ifndef RADIAL_BOX_H_
#define RADIAL_BOX_H_

#include "mowi/widget/widget.h"

void widget_input_radial_box(MowiWidget *widget);
void widget_render_radial_box(MowiWidget widget);
void widget_hover_radial_box(MowiWidget widget);

void widget_update_user_radial_box(MowiWidget widget);

void widget_create_radial_box(ToggleButton *toggle, int x, int y, char title[]);

#endif
