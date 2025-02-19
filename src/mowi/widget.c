#include <stdio.h>
#include <string.h>

#include "mowi/widget.h"
#include "mowi/widgets/text.h"
#include "mowi/widgets/rect.h"
#include "mowi/widgets/half-rect.h"
#include "mowi/widgets/action-button.h"
#include "mowi/widgets/toggle-button.h"
#include "mowi/widgets/list-box.h"
#include "mowi/widgets/radial-box.h"
#include "mowi/widgets/slider.h"
#include "mowi/widgets/text-box.h"

ActionButton *action_buttons[MAX_USER_WIDGETS_PER_TYPE] = {NULL};
ToggleButton *toggle_buttons[MAX_USER_WIDGETS_PER_TYPE] = {NULL};
ListBox      *list_boxes[MAX_USER_WIDGETS_PER_TYPE]     = {NULL};
RadialBox    *radial_boxes[MAX_USER_WIDGETS_PER_TYPE]   = {NULL};
Slider       *sliders[MAX_USER_WIDGETS_PER_TYPE]        = {NULL};

MowiWidget widgets[MAX_WIDGETS];
uint16_t   widgets_length = 0;

void mowi_add_widget(MowiWidget widget, int user_widget_index) {
    for (int i = 0; i < MAX_WIDGETS; i++) {
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

void input_click_widget_internal(MowiWidget *widget) {
	switch (widget->type) {
		case MOWI_TEXT:          { break; }
		case MOWI_RECT:          { break; }
		case MOWI_HALF_RECT:     { break; }
		case MOWI_ACTION_BUTTON: { widget_input_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_input_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_input_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_input_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_input_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_input_text_box(widget); break; }
	}
}

void renderer_render_widget(MowiWidget widget) {
	switch (widget.type) {
		case MOWI_TEXT: 		 { widget_render_text(widget); break; }
		case MOWI_RECT: 		 { widget_render_rect(widget); break; }
		case MOWI_HALF_RECT: 	 { widget_render_half_rect(widget); break; }
		case MOWI_ACTION_BUTTON: { widget_render_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_render_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_render_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_render_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_render_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_render_text_box(widget); break; }
	}
}

void renderer_hover_widget_internal(MowiWidget widget) {
	switch (widget.type) {
		case MOWI_TEXT:          { break; }
		case MOWI_RECT:          { break; }
		case MOWI_HALF_RECT:     { break; }
		case MOWI_ACTION_BUTTON: { widget_hover_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_hover_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_hover_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_hover_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_hover_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_hover_text_box(widget); break; }
	}
}

/* Updates the structs that the user uses to create widgets. */
void widget_user_update_internal(MowiWidget widget) {
    switch (widget.type) {
		case MOWI_ACTION_BUTTON: { widget_update_user_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_update_user_toggle_button(widget); break; }
		case MOWI_LIST_BOX:      { widget_update_user_list_box(widget); break; }
		case MOWI_RADIAL_BOX:    { widget_update_user_radial_box(widget); break; }
		case MOWI_SLIDER:        { widget_update_user_slider(widget); break; }
		case MOWI_TEXT_BOX:      { widget_update_user_text_box(widget); break; }
	}
}