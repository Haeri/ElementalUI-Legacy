#include "elem/node.h"

#include <iostream>
#include <map>

#include "elem/document.h"

namespace elem
{
	std::map<node*, int> node::_hover_map;


	void node::add_child(node* child)
	{
		_children.push_back(child);
		child->set_parent(this);
		set_document(_document);
	}

	void node::remove_child(int index)
	{
		node* elem = _children[index];
		remove_child(elem);
	}

	void node::remove_child(node* child)
	{
		_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
		child->set_parent(nullptr);
	}

	void node::set_state(State state)
	{
		_transition_progress = 0;

		if (style.transition_time <= 0) {
			if (state == HOVER_INITIAL) state = INITIAL;
			else if (state == INITIAL_HOVER) state = HOVER;
		}
		else
		{

		}
		_state = state;
	}

	void node::set_focus(bool focus)
	{
		_focused = focus;
	}

	void node::set_document(document* doc)
	{
		_document = doc;
		for (auto& child : _children)
		{
			child->set_document(doc);
		}
	}

	void node::add_click_listener(std::function<void(node_click_event)> callback)
	{
		_click_event_callbacks.push_back(callback);
	}

	int node::get_width()
	{
		return _width;
	}

	int node::get_height()
	{
		return _height;
	}

	elemd::vec2 node::get_position()
	{
		return _position;
	}

	void node::add_to_hover_list(node* node)
	{
		auto find = _hover_map.find(node);
		if (find == _hover_map.end()) {
			node->set_state(INITIAL_HOVER);
		}
		_hover_map[node] = 2;
	}

	void node::finish_hover_event()
	{
		for (auto it = _hover_map.begin(); it != _hover_map.end();)
		{
			it->second -= 1;
			if (it->second <= 0)
			{
				it->first->set_state(HOVER_INITIAL);
				_hover_map.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}

	void node::emit_click_event(elemd::mouse_button_event event)
	{
		for (auto& var : _click_event_callbacks)
		{
			var({ this, event });
		}

		if (_parent != nullptr)
		{
			_parent->emit_click_event(event);
		}
	}

	void node::emit_key_event(elemd::key_event event)
	{
		for (auto& var : _key_event_callbacks)
		{
			var({ this, event });
		}
	}

	void node::emit_char_event(elemd::char_event event)
	{
		for (auto& var : _char_event_callbacks)
		{
			var({ this, event });
		}
	}

	node* node::bounds_check(elemd::vec2 pos)
	{
		
		//std::cout << "Node: p" << "(" << _position.get_x() << ", " << _position.get_y() << ") " << " w" << get_width() << " h" << get_height();
		if ((pos.get_x() > _position.get_x() + style.margin[3] && pos.get_x() < _position.get_x() + (get_width() - style.margin[1])) &&
			(pos.get_y() > _position.get_y() + style.margin[0] && pos.get_y() < _position.get_y() + (get_height() - style.margin[2])))
		{
			add_to_hover_list(this);

			if (_children.size() != 0)
			{
				for (auto& el : _children)
				{
					node* ret = el->bounds_check(pos);
					if (ret != nullptr) {
						return ret;
					}
				}
				return this;
			}
			else
			{
				return this;
			}
		}

		//std::cout << std::endl;

		//hover = false;
		return nullptr;
	}

	elemd::vec2 node::get_minimum_dimensions(float available_width, float available_height)
	{
		elemd::vec2 child_pos = _position + elemd::vec2(style.margin[3] + style.padding[3], style.margin[0] + style.padding[0]);
		
		int index = 0;
		float width_accum = 0;
		float max_line_height = 0;

		float camc_width = 0;
		float calc_height = 0;

		for (node* el : _children) {

			//child_pos.y() += height_offset;

			float child_height = el->layout(child_pos + elemd::vec2(width_accum, calc_height), available_width, available_height);

			width_accum += el->get_width();
			if (max_line_height < el->get_height()) {
				max_line_height = el->get_height();
			}

			// Check if line is full
			if (_children.size() == (index + 1) || width_accum + _children[index + 1]->get_width() > available_width) {

				if (width_accum > camc_width) {
					camc_width = width_accum;
				}
				calc_height += max_line_height;

				width_accum = 0;
				max_line_height = 0;
			}

			++index;
		}
		return elemd::vec2(camc_width, calc_height);
	}

	float node::layout(elemd::vec2 position, float width, float height)
	{
		_position = position;

		float available_core_width = width - (style.margin[3] + style.padding[3]) - (style.margin[1] + style.padding[1]);
		float available_core_height = height - (style.margin[0] + style.padding[0]) - (style.margin[2] + style.padding[2]);

		// Handle Width

		switch (style.width.get_type())
		{
		case measure_value::Type::PERCENT:
			_width = width * (style.width.get_value() / 100.0f) + (style.margin[3]) + (style.margin[1]);
			available_core_width = _width;
			break;
		case measure_value::Type::PIXELS:
			_width = style.width.get_value() + (style.margin[3] + (style.margin[1]));
			available_core_width = _width;
			break;
		}

		
		// Handle minimum dimensions


		elemd::vec2 min_dims = get_minimum_dimensions(available_core_width, available_core_height);


		if (style.display == Display::BLOCK && style.width.get_type() == measure_value::Type::AUTO)
		{
			_width = width;
		}
		else if (style.display == Display::INLINE && style.width.get_type() == measure_value::Type::AUTO)
		{
			_width = min_dims.x() + (style.margin[3] + style.padding[3]) + (style.margin[1] + style.padding[1]);
		}
		

		
		// Handle Height


		switch (style.height.get_type())
		{
		case measure_value::Type::AUTO:
			_height = min_dims.y() + (style.margin[0] + style.padding[0]) + (style.margin[2] + style.padding[2]);
			break;
		case measure_value::Type::PERCENT:
			_height = height * (style.height.get_value() / 100.0f);
			break;
		case measure_value::Type::PIXELS:
			_height = style.height.get_value();
			break;
		}

		return _height;
	}

	void node::debug_paint(elemd::Context* ctx)
	{
		// DEBUG
		if (false) {
			//if (_state != INITIAL) {
				// Margin
			//ctx->set_line_width(1);
			ctx->set_fill_color(elemd::color("#ae815221"));
			ctx->fill_rect(
				_position.get_x(),
				_position.get_y(),
				_width,
				_height);

			// Padding
			ctx->set_fill_color(elemd::color("#b8c47f21"));
			ctx->fill_rect(
				_position.get_x() + style.margin[3],
				_position.get_y() + style.margin[0],
				_width - (style.margin[3] + style.margin[1]),
				_height - (style.margin[0] + style.margin[2]));

			// Content
			ctx->set_fill_color(elemd::color("#3e3e4221"));
			ctx->fill_rect(
				_position.get_x() + style.margin[3] + style.padding[3],
				_position.get_y() + style.margin[0] + style.padding[0],
				_width - (style.margin[3] + style.margin[1]) - (style.padding[3] + style.padding[1]),
				_height - (style.margin[0] + style.margin[2]) - (style.padding[0] + style.padding[2]));

			ctx->set_fill_color(elemd::color(200, 200, 200));
			ctx->set_font_size(9);
			ctx->draw_text(_position.get_x()+2.0f,
				_position.get_y(), id);

		}

	}

	void node::destroy()
	{
		_should_destroy = true;
	}

	void node::destroy_immediately()
	{
		for (auto& child : _children)
		{
			child->destroy();
		}
		_parent = nullptr;

		delete this;
	}

	void node::set_parent(node* parent)
	{
		_parent = parent;

		if (parent != nullptr)
		{
			_document = parent->_document;
		}
	}

}// namespace elem