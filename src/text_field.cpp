#include "elem/text_field.h"

namespace elem
{
	text_field::text_field()
	{
	}
	void text_field::emit_key_event(elemd::key_event event)
	{
		node::emit_key_event(event);
	
		if (event.action == elemd::ACTION_PRESS || event.action == elemd::ACTION_REPEAT)
		{
			switch (event.key)
			{


			case elemd::keyboard_key::KEY_LEFT:
				if (_cursor_pos > 0)
				{
					--_cursor_pos;
				}
				break;
			case elemd::keyboard_key::KEY_RIGHT:
				if (_cursor_pos <= _content.length())
				{
					++_cursor_pos;
				}
				break;

			case elemd::keyboard_key::KEY_BACKSPACE:
				if (_cursor_pos > 0)
				{
					_content.erase(_cursor_pos-1, 1);
					--_cursor_pos;
				}
				break;

			case elemd::keyboard_key::KEY_DELETE:
				if (_cursor_pos < _content.length())
				{
					_content.erase(_cursor_pos, 1);
				}
				break;

			}
		}
	}

	void text_field::emit_char_event(elemd::char_event event)
	{
		node::emit_char_event(event);

		_content.insert(_cursor_pos, event.utf8);
		++_cursor_pos;
	}

	float text_field::layout(elemd::vec2 position, float width, float height)
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
	}

	void text_field::paint(elemd::Context* ctx)
	{
		if (_focused)
		{
			elemd::vec2 dim = style.font_family->measure_dimensions(_content.substr(0, _cursor_pos), style.font_size);

			ctx->set_fill_color(style.color);
			ctx->fill_rect(
				_position.get_x() + style.margin[3] + style.padding[3] + dim.x(), 
				_position.get_y() + style.margin[0] + style.padding[0],
				1,
				style.font_size);
		}

		ctx->set_font(style.font_family);
		ctx->set_font_size(style.font_size);
		ctx->set_fill_color(style.color);
		ctx->draw_text(_position.get_x() + style.margin[3] + style.padding[3], _position.get_y() + style.margin[0] + style.padding[0], _formated_content);

	}

	void text_field::set_text(std::string text)
	{
		_content = text;
	}

	std::string text_field::get_text()
	{
		return _content;
	}
}