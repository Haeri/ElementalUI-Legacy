#include "elem/element.h"

#include <algorithm>

#include <elem/document.h>

namespace elem
{

	void element::paint(elemd::Context* ctx)
	{
		elemd::color bg = style.background_color;
		if ((_state == HOVER || _state == INITIAL_HOVER || _state == HOVER_INITIAL) && style.background_color != hover_style.background_color) {
			float percent = _transition_progress / style.transition_time;
			percent = std::min(std::max(percent, 0.0f), 1.0f);

			if (_state == INITIAL_HOVER)
			{
				bg = elemd::color::color_lerp(style.background_color, hover_style.background_color, percent);
				_document->request_high_frequency();
			}
			else if (_state == HOVER_INITIAL)
			{
				bg = elemd::color::color_lerp(hover_style.background_color, style.background_color, percent);
				_document->request_high_frequency();
			}
			else if (_state == HOVER)
			{
				bg = hover_style.background_color;
			}

			_transition_progress += _document->delta_time;
		}
		
		
		if (_transition_progress >= style.transition_time) {
			if (_state == INITIAL_HOVER) _state = HOVER;
			else if (_state == HOVER_INITIAL) _state = INITIAL;
		}


		// Background
		if (bg.a() != 0) {
			ctx->set_fill_color(bg);
			ctx->fill_rounded_rect(
				_position.get_x() + style.margin[3],
				_position.get_y() + style.margin[0],
				_width - (style.margin[3] + style.margin[1]),
				_height - (style.margin[0] + style.margin[2]),
				style.border_radius[0], style.border_radius[1], style.border_radius[2], style.border_radius[3]);
		}

		// Border
		if (style.border_color.a() != 0 && style.border_width != 0) {
			ctx->set_stroke_color(style.border_color);
			ctx->set_line_width(style.border_width);
			ctx->stroke_rect(
				_position.get_x() + style.margin[3] + style.padding[3],
				_position.get_y() + style.margin[0] + style.padding[0],
				_width - (style.margin[3] + style.margin[1]) - (style.padding[3] + style.padding[1]),
				_height - (style.margin[0] + style.margin[2]) - (style.padding[0] + style.padding[2]));
		}


		if(_state == HOVER || _state == INITIAL_HOVER)
			debug_paint(ctx);
		
		for (node* el : _children) {
			el->paint(ctx);
		}
	}
}