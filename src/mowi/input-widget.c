
#include "mowi/renderer-widget.h"
#include "common/color.h"
#include "mowi/widget.h"
#include "mowi/input.h"

void input_click_widget(Widget *widget) {
	switch (widget->type) {
		case MOWI_TEXT: { break; }
		case MOWI_RECT: { break; }
		case MOWI_HALF_RECT: { break; }
		case MOWI_ACTION_BUTTON: {
            if (screen_x >= widget->x && screen_x < widget->x+widget->action_button_title_length && screen_y == widget->y) {
                widget->action_button_on_click();
            }
			break;
		}
		case MOWI_TOGGLE_BUTTON: {  
			if (screen_x >= widget->x && screen_x < widget->x+widget->toggle_button_title_length+4 && screen_y == widget->y) {
                if (widget->toggle_button_state == 0) {
                    widget->toggle_button_state = 1;
                    mowi_set_pixel(widget->x+1, widget->y, '+', default_pop_color);
                    renderer_set_pixel(widget->x+1, widget->y);
                }
                else if (widget->toggle_button_state == 1) {
                    widget->toggle_button_state = 0;
                    mowi_set_pixel(widget->x+1, widget->y, ' ', default_fg_color);
                    renderer_set_pixel(widget->x+1, widget->y);
                }
            }
			break;
		}
		case MOWI_LIST_BOX: {
            for (int i = 0; i < widget->list_box_length; i++) {
				if (screen_x >= widget->x+1 && screen_x < widget->x+2+widget->list_box_options_internal[i].title_length && screen_y == widget->y+1+widget->list_box_options_internal[i].index) {
                    if (widget->list_box_options_internal[i].is_selected == false) {
                        mowi_set_pixel(widget->x+1, widget->y+1+i, '+', default_pop_color);
                        renderer_set_pixel(widget->x+1, widget->y+1+i);
                        widget->list_box_options_internal[i].is_selected = true;
                    }
                    else {
                        mowi_set_pixel(widget->x+1, widget->y+1+i, ' ', default_pop_color);
                        renderer_set_pixel(widget->x+1, widget->y+1+i);
                        widget->list_box_options_internal[i].is_selected = false;

                    }
                }
            }
			break;
		}
		case MOWI_RADIAL_BOX: {
			for (int i = 0; i < widget->radial_box_length; i++) {
				if (screen_x >= widget->x+1 && screen_x < widget->x+2+widget->radial_box_options_internal[i].title_length && screen_y == widget->y+1+widget->radial_box_options_internal[i].index) {
                    if (widget->radial_box_options_internal[i].is_selected == false) {
                        mowi_set_pixel(widget->x+1, widget->y+1+i, '>', default_pop_color);
                        renderer_set_pixel(widget->x+1, widget->y+1+i);
                        widget->radial_box_options_internal[i].is_selected = true;
                        for (int j = 0; j < widget->radial_box_length; j++) {
                            if (j==i) continue;
                            widget->radial_box_options_internal[j].is_selected = false;
                        }
                        renderer_hover_widget(*widget);
                    }
                    else {
                        mowi_set_pixel(widget->x+1, widget->y+1+i, ' ', default_pop_color);
                        renderer_set_pixel(widget->x+1, widget->y+1+i);
                        widget->radial_box_options_internal[i].is_selected = false;

                    }
                }
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
}
