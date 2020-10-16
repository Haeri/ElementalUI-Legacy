#include "..\include\elem\node.h"

#include <iostream>

#include "elem/document.h"

namespace elem
{
	std::vector<node*> node::_hover_list;

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
		_hover_list.push_back(node);	
	}

	void node::clear_hover_list()
	{
		for (auto& node : _hover_list)
		{
			node->hover = false;
		}

		_hover_list.clear();
	}

	bool node::bounds_check(elemd::vec2 pos)
	{
		
		//std::cout << "Node: p" << "(" << _position.get_x() << ", " << _position.get_y() << ") " << " w" << get_width() << " h" << get_height();
		if ((pos.get_x() > _position.get_x() + style.margin[3] && pos.get_x() < _position.get_x() + (get_width() - style.margin[1])) &&
			(pos.get_y() > _position.get_y() + style.margin[0] && pos.get_y() < _position.get_y() + (get_height() - style.margin[2])))
		{
			hover = true;
			add_to_hover_list(this);
			//std::cout << " - HOVER" << std::endl;

			for (auto& el : _children)
			{
				if (el->bounds_check(pos)) {
					break;
				}
			}


			return true;
		}

		//std::cout << std::endl;

		hover = false;
		return false;
	}

	void node::set_parent(node* parent)
	{
		_parent = parent;
	}

}// namespace elem