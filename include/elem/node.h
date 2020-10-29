#ifndef ELEM_NODE_H
#define ELEM_NODE_H

#include "elem/elemental_ui.h"

#include <vector>
#include <functional>

#include <elemd/vec2.hpp>
#include <elemd/context.hpp>
#include <elemd/font.hpp>
#include <elemd/event.hpp>

#include "measure_value.h"

class document;

namespace elem
{
    class ELEM_API node
    {
    public:
        enum Display {
            BLOCK,
            INLINE
        };

        enum State {
            INITIAL,
            INITIAL_HOVER,
            HOVER,
            HOVER_INITIAL
        };

        // Style
        struct Style {
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
            float font_size = 10;
            float border_radius[4] = { 0, 0, 0, 0 };
            float border_width = 0;
            elemd::color border_color = elemd::color(0, 0, 0, 255);
            elemd::image* background_image = nullptr;
            float transition_time;
        };


        struct click_event {
            class node* node;   // GCC needs help here. class declaration is required
            elemd::mouse_button_event event;
        };


        
        Style hover_style;
        Style style;

        std::string id;
        std::string class_name;

        void add_child(node* child);
        void remove_child(int index);
        void remove_child(node* child);

        void set_state(State state);
        void add_click_listener(std::function<void(click_event)> callback);

        int get_width();
        int get_height();
        elemd::vec2 get_position();

        static void add_to_hover_list(node* node);
        static void finish_hover_event();

        virtual void emit_click_event(elemd::mouse_button_event mouse_event);
        virtual node* bounds_check(elemd::vec2 pos);
        virtual float layout(elemd::vec2 position, float width) = 0;
        virtual void paint(elemd::Context* ctx) = 0;

    protected:
        static std::map<node*, int> _hover_map;

        node* _parent = nullptr;
        std::vector<node*> _children;
        std::vector<std::function<void(click_event)>> _click_event_callbacks;

        State _state = INITIAL;
        float _transition_progress;
        elemd::vec2 _position = elemd::vec2(-1, -1);
        float _width = -1;
        float _height = -1;

        void set_parent(node* parent);


    };
} // namespace elem

#endif // ELEM_NODE_H