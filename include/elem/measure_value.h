#ifndef ELEM_MEASURE_VALUE_H
#define ELEM_MEASURE_VALUE_H

#include <elem/elemental_ui.h>

#include <string>

namespace elem
{
    class ELEM_API measure_value
    {
    public:

        enum Type {
            PIXELS,
            PERCENT,
            AUTO
        };

        measure_value() {}
        measure_value(std::string value);
        measure_value(float value, Type type);

        void set_pixels(float pixels);
        void set_percent(float percent);

        float get_value();
        Type get_type();

    private:
        Type _type = Type::AUTO;
        float _value = -1;
    };
} // namespace elem

#endif // ELEM_MEASURE_VALUE_H