#ifndef TEXT_H_
#define TEXT_H_

#include "mowi/widget/widget.h"

void widget_input_text(MowiWidget *widget);
void widget_render_text(MowiWidget widget);
void widget_hover_text(MowiWidget widget);

void widget_update_user_text(MowiWidget widget);

void widget_create_text(ToggleButton *toggle, int x, int y, char title[]);

#endif
