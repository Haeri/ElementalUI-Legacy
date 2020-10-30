#include "elem/element.h"

#include <algorithm>

#include <elem/document.h>

namespace elem
{
	float element::layout(elemd::vec2 position, float width)
	{
		_position = position;

		if (style.display == Display::BLOCK && style.width.get_type() == measure_value::Type::AUTO)
		{
			_width = width;
		}

		switch (style.width.get_type())
		{
		case measure_value::Type::AUTO:
			break;
		case measure_value::Type::PERCENT:
			_width = width * (style.width.get_value() / 100.0f);
			break;
		case measure_value::Type::PIXELS:
			_width = style.width.get_value();
			break;
		}

		elemd::vec2 child_pos = position + elemd::vec2(style.margin[3] + style.padding[3], style.margin[0] + style.padding[0]);
		float child_width = width - (style.margin[3] + style.padding[3]) - (style.margin[1] + style.padding[1]);
		float height_offset = 0;
		int index = 0;
		float width_accum = 0;
		float max_line_height = 0;
		float tmp_width = 0;
		_height = 0;

		for (node* el : _children) {

			//child_pos.y() += height_offset;

			float child_height = el->layout(child_pos + elemd::vec2(width_accum, _height), child_width);

			width_accum += el->get_width();
			if (max_line_height < el->get_height()) {
				max_line_height = el->get_height();
			}

			// Check if line is full
			if (_children.size() == (index + 1) || width_accum + _children[index + 1]->get_width() > child_width) {

				if (width_accum > tmp_width) {
					tmp_width = width_accum;
				}
				_height += max_line_height;

				width_accum = 0;
				max_line_height = 0;
			}

			++index;
		}
		_height += (style.margin[0] + style.padding[0]) + (style.margin[2] + style.padding[2]);

		if (style.display == Display::INLINE && style.width.get_type() == measure_value::Type::AUTO)
		{
			_width = tmp_width + (style.margin[3] + style.padding[3]) + (style.margin[1] + style.padding[1]);
		}

		return _height;
	}

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
		


		// DEBUG
		if (false) {
		//if (_state != INITIAL) {
			// Margin
			ctx->set_line_width(1);
			ctx->set_stroke_color(elemd::color("#ae8152"));
			ctx->stroke_rect(
				_position.get_x(),
				_position.get_y(),
				_width,
				_height);

			// Padding
			ctx->set_stroke_color(elemd::color("#b8c47f"));
			ctx->stroke_rect(
				_position.get_x() + style.margin[3],
				_position.get_y() + style.margin[0],
				_width - (style.margin[3] + style.margin[1]),
				_height - (style.margin[0] + style.margin[2]));

			// Content
			ctx->set_stroke_color(elemd::color("#3e3e42"));
			ctx->stroke_rect(
				_position.get_x() + style.margin[3] + style.padding[3],
				_position.get_y() + style.margin[0] + style.padding[0],
				_width - (style.margin[3] + style.margin[1]) - (style.padding[3] + style.padding[1]),
				_height - (style.margin[0] + style.margin[2]) - (style.padding[0] + style.padding[2]));
		
		}

		for (node* el : _children) {
			el->paint(ctx);
		}
	}
}