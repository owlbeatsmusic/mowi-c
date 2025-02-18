#include <stdio.h>
#include <string.h>

#include "mowi/widget/widget.h"
#include "mowi/widget/widgets/action-button.h"

ActionButton *action_buttons[32] = {NULL};
ToggleButton *toggle_buttons[32] = {NULL};
ListBox      *list_boxes[32]     = {NULL};
RadialBox    *radial_boxes[32]   = {NULL};
Slider       *sliders[32]        = {NULL};

MowiWidget widgets[64];
uint16_t   widgets_length = 0;

void mowi_add_widget(MowiWidget widget, int user_widget_index) {
    for (int i = 0; i < 64; i++) {
        if (widgets[i].type == NONE) {
            widgets[i] = widget;
            widgets[i].index = i;
            widgets[i].user_widget_index = user_widget_index;
            widgets_length++;
            switch (widgets[i].type) {
                case MOWI_LIST_BOX: {
                    for (int j = 0; j < widgets[i].list_box_length; j++) {
                        BoxOption option = { .index = j, .is_selected = false, .title_length=strlen(widgets[i].list_box_all_options[j]) };
                        strcpy(option.title, widgets[i].list_box_all_options[j]);
                        widgets[i].list_box_options_internal[j] = option;   
                    }
                    break;
                }
                case MOWI_RADIAL_BOX: {
                    for (int j = 0; j < widgets[i].radial_box_length; j++) {
                        BoxOption option = { .index = j, .is_selected = false, .title_length=strlen(widgets[i].radial_box_all_options[j]) };
                        strcpy(option.title, widgets[i].radial_box_all_options[j]);
                        widgets[i].radial_box_options_internal[j] = option;   
                    }
                    break;
                }
                case MOWI_SLIDER: {
                    
                    break;
                }
                case MOWI_TEXT_BOX: {
                    
                    break;
                }
                case MOWI_CONSOLE: {
                    
                    break;
                }
            }
            break;
        }
    }
}


/* Updates the structs that the user uses to create widgets. */
void widget_user_update(MowiWidget widget) {
    switch (widget.type) {
		case MOWI_ACTION_BUTTON: { widget_update_user_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_update_user_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { break; }
		case MOWI_RADIAL_BOX:    { break; }
		case MOWI_SLIDER:        { break; }
		case MOWI_TEXT_BOX:      { break; }
		case MOWI_CONSOLE:       { break; }
	}
}