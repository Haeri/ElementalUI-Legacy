#include "elem/heading.h"

namespace elem
{
	heading::heading()
	{
		style.display = Display::INLINE;
	}

	/*
	float heading::layout(elemd::vec2 position, float width, float height)
	{
		_position = position;
		_width = width;
		float w_style = (style.margin[4] + style.padding[4]) + (style.margin[1] + style.padding[1]);
		float h_style = (style.margin[0] + style.padding[0]) + (style.margin[2] + style.padding[2]);
		float w_space = width - w_style;

		_formated_content = style.font_family->fit_substring(get_text(), w_space, style.font_size);
		elemd::vec2 dim = style.font_family->measure_dimensions(_formated_content, style.font_size);

		_height = dim.get_y() + h_style;
		if (style.display == INLINE) {
			_width = dim.get_x() + w_style;
		}

		return _height;
	}*/

	elemd::vec2 heading::get_minimum_dimensions(float width, float height)
	{
		_formated_content = style.font_family->fit_substring(get_text(), width, style.font_size);
		return style.font_family->measure_dimensions(_formated_content, style.font_size);
	}

	void heading::paint(elemd::Context* ctx)
	{
		ctx->set_font(style.font_family);
		ctx->set_font_size(style.font_size);
		ctx->set_fill_color(style.color);
		ctx->draw_text(_position.get_x() + style.margin[3] + style.padding[3], _position.get_y() + style.margin[0] + style.padding[0], _formated_content);



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
	}

	void heading::set_text(std::string text)
	{
		_content = text;
	}

	std::string heading::get_text()
	{
		return _content;
	}
}