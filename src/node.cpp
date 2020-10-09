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

	void node::set_parent(node* parent)
	{
		_parent = parent;
	}

}// namespace elem