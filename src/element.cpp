#include "..\include\elem\element.h"

#include <algorithm>

namespace elem
{
	element::element()
	{
	}

	void element::add_child(element* child)
	{
		_children.push_back(child);
		child->set_parent(this);
	}

	void element::remove_child(int index)
	{
		element* elem = _children[index];
		remove_child(elem);
	}

	void element::remove_child(element* child)
	{
		_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
		child->set_parent(nullptr);
	}

	float element::layout(elemd::vec2 position, float width)
	{
		_position = position;

		if (style.display == Display::BLOCK)
		{
			_width = width;
		}

		elemd::vec2 child_pos = position + elemd::vec2(style.margin[3] + style.padding[3], style.margin[0] + style.padding[0]);
		float child_width = width - (style.margin[3] + style.padding[3]) - (style.margin[1] + style.padding[1]);
		float height_offset = 0;
		int index = 0;
		float width_accum = 0;
		float max_line_height = 0;
		float tmp_width = 0;
		_height = 0;

		for (element* el : _children) {

			//child_pos.y() += height_offset;

			float child_height = el->layout(child_pos + elemd::vec2(width_accum, _height), child_width);

			width_accum += el->_width;
			if (max_line_height < el->_height) {
				max_line_height = el->_height;
			}

			// Check if line is full
			if (_children.size() == (index + 1) || width_accum + _children[index + 1]->_width > child_width) {

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

		if (style.display == Display::INLINE)
		{
			_width = tmp_width + (style.margin[3] + style.padding[3]) + (style.margin[1] + style.padding[1]);
		}

		return _height;
	}

	void element::paint(elemd::Context* ctx)
	{

		if (style.border_radius[0] != 0 || style.border_radius[1] != 0 || style.border_radius[2] != 0 || style.border_radius[3] != 0) {
			ctx->set_fill_color(style.background_color);
			ctx->fill_rounded_rect(
				_position.get_x() + style.margin[3],
				_position.get_y() + style.margin[0],
				_width - (style.margin[3] + style.margin[1]),
				_height - (style.margin[0] + style.margin[2]),
				style.border_radius[0], style.border_radius[1], style.border_radius[2], style.border_radius[3]);
		}
		else {
			ctx->set_fill_color(style.background_color);
			ctx->fill_rect(
				_position.get_x() + style.margin[3],
				_position.get_y() + style.margin[0],
				_width - (style.margin[3] + style.margin[1]),
				_height - (style.margin[0] + style.margin[2]));
		}

		if (style.border_color.a() != 0 || style.border_width != 0) {
			if (style.border_radius[0] != 0 || style.border_radius[1] != 0 || style.border_radius[2] != 0 || style.border_radius[3] != 0)
			{

			}
			else
			{

			}
		}


		// DEBUG

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


		for (element* el : _children) {
			el->paint(ctx);
		}
	}



	void element::set_parent(element* parent)
	{
		_parent = parent;
	}

}