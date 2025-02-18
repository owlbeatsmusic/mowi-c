#ifndef LIST_BOX_H_
#define LIST_BOX_H_

#include "mowi/widget/widget.h"

void widget_input_list_box(MowiWidget *widget);
void widget_render_list_box(MowiWidget widget);
void widget_hover_list_box(MowiWidget widget);

void widget_update_user_list_box(MowiWidget widget);

void widget_create_list_box(ToggleButton *list_box, int x, int y, char title[]);

#endif
