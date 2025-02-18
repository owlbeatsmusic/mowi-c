
#include "common/color.h"
#include "mowi/widget/widget.h"
#include "mowi/input.h"

#include "mowi/widget/widgets/action-button.h"
#include "mowi/widget/widgets/toggle-button.h"


void renderer_render_widget(MowiWidget widget) {
	switch (widget.type) {
		case MOWI_TEXT: {
			for (int i = 0; i < widget.text_length; i ++) {
				mowi_set_pixel(widget.x+i, widget.y, widget.text[i], default_fg_color);
			}
			break;
		}
		case MOWI_RECT: {
			mowi_set_pixel(widget.x, 				   widget.y, 					    '.', default_fg_color);
			mowi_set_pixel(widget.x+widget.rect_width-1, widget.y,					    '.', default_fg_color);
			mowi_set_pixel(widget.x, 				   widget.y+widget.rect_height-1,   '\'', default_fg_color);
			mowi_set_pixel(widget.x+widget.rect_width-1, widget.y+widget.rect_height-1, '\'', default_fg_color);

			for (int i = 1; i < widget.rect_width-1; i++) {
				mowi_set_pixel(widget.x+i, widget.y, 					  '-', default_fg_color);
				mowi_set_pixel(widget.x+i, widget.y+widget.rect_height-1, '-', default_fg_color);
			}
			for (int i = 1; i < widget.rect_height-1; i++) {
				mowi_set_pixel(widget.x, widget.y+i, 					  '|', default_fg_color);
				mowi_set_pixel(widget.x+widget.rect_width-1, widget.y+i,  '|', default_fg_color);
			}

			break;
		}
		case MOWI_HALF_RECT: {
			mowi_set_pixel(widget.x, 				  		  widget.y, 					      '.', default_fg_color);
			mowi_set_pixel(widget.x+widget.half_rect_width-1, widget.y,					          '.', default_fg_color);
			mowi_set_pixel(widget.x, 				          widget.y+widget.half_rect_height-1, '\'', default_fg_color);
			mowi_set_pixel(widget.x+widget.half_rect_width-1, widget.y+widget.half_rect_height-1, '\'', default_fg_color);

			for (int i = 1; i < widget.half_rect_width-1; i++) {
				mowi_set_pixel(widget.x+i, widget.y, 				           '-', default_fg_color);
				mowi_set_pixel(widget.x+i, widget.y+widget.half_rect_height-1, '-', default_fg_color);
			}
			for (int i = 1; i < widget.half_rect_height-1; i++) {
				mowi_set_pixel(widget.x, widget.y+i, 					  '|', default_fg_color);
			}
			break;
		}
		case MOWI_ACTION_BUTTON: { widget_render_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_render_toggle_button(widget); break; }
		case MOWI_LIST_BOX: {
			MowiWidget half_rect = {.type = MOWI_HALF_RECT, .x = widget.x, .y = widget.y, .half_rect_width = 3, .half_rect_height = widget.list_box_length+2};
			renderer_render_widget(half_rect);

			// title
			mowi_set_pixel(widget.x+2, widget.y, '[', default_fg_color);
			for (int i = 0; i < strlen(widget.list_box_title); i ++) {
				mowi_set_pixel(widget.x+3+i, widget.y, widget.list_box_title[i], default_fg_color);
			}
			mowi_set_pixel(widget.x+3+strlen(widget.list_box_title), widget.y, ']', default_fg_color);
			
			// options
			for (int i = 0; i < widget.list_box_length; i ++) {
				if (widget.list_box_options_internal[i].is_selected == 1) {
					mowi_set_pixel(widget.x+1, widget.y+1+i, '+', default_pop_color);
				}
				else {
					mowi_set_pixel(widget.x+1, widget.y+1+i, ' ', default_fg_color);
				}
				for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
                    mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
                }
			}
			if (widget.list_box_show_counter == true) {
				// TODO: 
			}

			break;
		}
		case MOWI_RADIAL_BOX: {
		    MowiWidget half_rect = {.type = MOWI_HALF_RECT, .x = widget.x, .y = widget.y, .half_rect_width = 3, .half_rect_height = widget.radial_box_length+2};
			renderer_render_widget(half_rect);

			// title
			mowi_set_pixel(widget.x+2, widget.y, '[', default_fg_color);
			for (int i = 0; i < strlen(widget.radial_box_title); i ++) {
				mowi_set_pixel(widget.x+3+i, widget.y, widget.radial_box_title[i], default_fg_color);
			}
			mowi_set_pixel(widget.x+3+strlen(widget.radial_box_title), widget.y, ']', default_fg_color);

			// options
			for (int i = 0; i < widget.radial_box_length; i ++) {
				if (widget.radial_box_options_internal[i].is_selected == 1) {
					mowi_set_pixel(widget.x+1, widget.y+1+i, '>', default_pop_color);
				}
				else {
					mowi_set_pixel(widget.x+1, widget.y+1+i, ' ', default_fg_color);
				}
				for (int j = 0; j < widget.radial_box_options_internal[i].title_length; j++) {
                    mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.radial_box_options_internal[i].title[j], default_fg_color);
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

void renderer_hover_widget(MowiWidget widget) {
	switch (widget.type) {
		case MOWI_TEXT: { break; }
		case MOWI_RECT: { break; }
		case MOWI_HALF_RECT: { break; }
		case MOWI_ACTION_BUTTON: { widget_hover_action_button(widget); break; }
		case MOWI_TOGGLE_BUTTON: { widget_hover_toggle_button(widget); break; }
		case MOWI_LIST_BOX: {
			for (int i = 0; i < widget.list_box_length; i++) {
				if (screen_x >= widget.x+1 && screen_x < widget.x+2+widget.list_box_options_internal[i].title_length && screen_y == widget.y+1+widget.list_box_options_internal[i].index) {
					for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
						mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_pop_color);
						renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

					}
				} 
				else {
					for (int j = 0; j < widget.list_box_options_internal[i].title_length; j++) {
						mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.list_box_options_internal[i].title[j], default_fg_color);
						renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

					}
				}
			}
			break;
		}
		case MOWI_RADIAL_BOX: {
			for (int i = 0; i < widget.radial_box_length; i++) {
				if (screen_x >= widget.x+1 && screen_x < widget.x+2+widget.radial_box_options_internal[i].title_length && screen_y == widget.y+1+widget.radial_box_options_internal[i].index) {
					if (widget.radial_box_options_internal[i].is_selected == true) {
                        mowi_set_pixel(widget.x+1, widget.y+1+i, '>', default_pop_color);
                        renderer_set_pixel(widget.x+1, widget.y+1+i);
                    }
                    renderer_set_pixel(widget.x+1, widget.y+1+i);
                    for (int j = 0; j < widget.radial_box_options_internal[i].title_length; j++) {
						mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.radial_box_options_internal[i].title[j], default_pop_color);
						renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

					}
				} 
				else {
                    if (widget.radial_box_options_internal[i].is_selected == true) {
                        mowi_set_pixel(widget.x+1, widget.y+1+i, '-', default_fg_color);
                        renderer_set_pixel(widget.x+1, widget.y+1+i);
                    }
                    else {
                        mowi_set_pixel(widget.x+1, widget.y+1+i, ' ', default_fg_color);
                        renderer_set_pixel(widget.x+1, widget.y+1+i);
                    }
					for (int j = 0; j < widget.radial_box_options_internal[i].title_length; j++) {
						mowi_set_pixel(widget.x + 2 + j, widget.y + 1 + i, widget.radial_box_options_internal[i].title[j], default_fg_color);
						renderer_set_pixel(widget.x + 2 + j, widget.y + 1 + i);

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
