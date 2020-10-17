#include "elem/heading.h"

elem::heading::heading()
{
	style.display = Display::INLINE;
}

float elem::heading::layout(elemd::vec2 position, float width)
{
	_position = position;
	_width = width;

	style.font_family->get_size();

	_height = style.font_family->get_size() * 0.5f + (style.margin[0] + style.padding[0]) + (style.margin[2] + style.padding[2]);

	return _height;
}

void elem::heading::paint(elemd::Context* ctx)
{
	ctx->set_font(style.font_family);
	ctx->set_fill_color(style.color);
	ctx->draw_text(_position.get_x() + style.margin[3] + style.padding[3], _position.get_y() + style.margin[0] + style.padding[0], _content);



	// DEBUG
	if (false) {
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
			_position.get_x() + style.margin[3] + style.padding[3],
			_position.get_y() + style.margin[0] + style.padding[0],
			_width - (style.margin[3] + style.margin[1]) - (style.padding[3] + style.padding[1]),
			_height - (style.margin[0] + style.margin[2]) - (style.padding[0] + style.padding[2]));
	}
}

void elem::heading::set_text(std::string text)
{
	_content = text;
}

std::string elem::heading::get_text()
{
	return _content;
}
