#ifndef ELEM_NODE_H
#define ELEM_NODE_H

#include "elem/elemental_ui.h"

#include <vector>

#include <elemd/vec2.hpp>
#include <elemd/Context.hpp>
#include <elemd/font.hpp>

#include "measure_value.h"

namespace elem
{
    class ELEM_API node
    {
    public:
        enum Display {
            BLOCK,
            INLINE
        };

        // Style
        struct style {
            Display display = Display::BLOCK;
            measure_value width;
            measure_value height;
            float min_width = -1;
            float min_height = -1;
            float max_width = std::numeric_limits<float>::max();
            float max_height = std::numeric_limits<float>::max();
            float padding[4] = { 0, 0, 0, 0 };
            float margin[4] = { 0, 0, 0, 0 };
            elemd::color background_color = elemd::color(0, 0, 0, 0);
            elemd::color color = elemd::color(0, 0, 0, 255);
            elemd::font* font_family = nullptr;
            float border_radius[4] = { 0, 0, 0, 0 };
            float border_width = 0;
            elemd::color border_color = elemd::color(0, 0, 0, 255);
            elemd::image* background_image = nullptr;
        } style;

        std::string id;
        std::string class_name;

        void add_child(node* child);
        void remove_child(int index);
        void remove_child(node* child);

        int get_width();
        int get_height();

        virtual float layout(elemd::vec2 position, float width) = 0;
        virtual void paint(elemd::Context* ctx) = 0;

    protected:
        node* _parent = nullptr;
        std::vector<node*> _children;

        elemd::vec2 _position = elemd::vec2(-1, -1);
        float _width = -1;
        float _height = -1;

        void set_parent(node* parent);
    };
} // namespace elem

#endif // ELEM_NODE_H