#include "elem/measure_value.h"

#include <iostream>
#include <algorithm>

namespace elem
{
	value::value(std::string value)
	{
		std::size_t found = value.find("px");
		if (found != std::string::npos)
		{
			_value = std::stof(value.substr(0, found));
			_type = Type::PIXELS;
			return;
		}

		found = value.find("%");
		if (found != std::string::npos)
		{
			_value = std::stof(value.substr(0, found));
			_type = Type::PERCENT;
			return;
		}

		std::cerr << "Error: " << value << " format not recognized!" << std::endl;
	}

	value::value(float value, Type type)
	{
		_value = value;
		_type = type;
	}

	void value::set_pixels(float pixels)
	{
		_value = pixels;
		_type = Type::PIXELS;
	}

	void value::set_percent(float percent)
	{
		_value = percent;
		_type = Type::PERCENT;
	}

	float value::get_value()
	{
		return _value;
	}

	value::Type elem::value::get_type()
	{
		return _type;
	}

}