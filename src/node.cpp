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

	void node::destroy()
	{
		for (auto& child : _children)
		{
			child->destroy();
		}

		delete this;
	}

	void node::set_parent(node* parent)
	{
		_parent = parent;
		_document = parent->_document;
	}

}// namespace elem