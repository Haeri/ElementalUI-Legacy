#ifndef ELEM_ELEMENT_HPP
#define ELEM_ELEMENT_HPP

#include <elem/elemental_ui.h>
#include <vector>
#include <limits> 

#include <elemd/vec2.hpp>
#include <elemd/color.hpp>
#include <elemd/Context.hpp>

namespace elem
{
    class ELEM_API element
    {
    public:
        enum Display {
            BLOCK,
            INLINE
        };


        uint32_t id;
        std::string class_name;

        // Style
        struct style{
            Display display = Display::BLOCK;
            float width = -1;
            float height = -1;
            float min_width = -1;
            float min_height = -1;
            float max_width = std::numeric_limits<float>::max();
            float max_height = std::numeric_limits<float>::max();
            float padding[4] = {0, 0, 0, 0};
            float margin[4] = { 0, 0, 0, 0 };
            elemd::color background_color = elemd::color(0, 0, 0, 0);
            elemd::color color = elemd::color(0, 0, 0, 255);
            float border_radius[4] = { 0, 0, 0, 0 };
            float border_width = 0;
            elemd::color border_color = elemd::color(0, 0, 0, 255);
            elemd::image* background_image = nullptr;
        } style;

        element();
        //element(element* parent);

        void add_child(element* child);
        void remove_child(int index);
        void remove_child(element* child);
        
        float layout(elemd::vec2 position, float width);
        void paint(elemd::Context* ctx);
    private:
        elemd::vec2 _position = elemd::vec2(-1, -1);
        float _width = -1;
        float _height = -1;

        element* _parent = nullptr;
        std::vector<element*> _children;

        void set_parent(element* parent);
    };
} // namespace elem

#endif // ELEM_ELEMENT_HPP