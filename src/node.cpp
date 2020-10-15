#include "..\include\elem\node.h"

namespace elem
{

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

	bool node::bounds_check(elemd::vec2 pos)
	{
		if (pos.get_x() > _position.get_x() || pos.get_x() < _position.get_x() + get_width() &&
			pos.get_y() > _position.get_y() || pos.get_y() < _position.get_y() + get_height())
		{
			hover = true;

			for (auto& el : _children)
			{
				if (el->bounds_check(pos)) {
					break;
				}
			}

			return true;
		}

		hover = false;
		return false;
	}

	void node::set_parent(node* parent)
	{
		_parent = parent;
	}

}// namespace elem