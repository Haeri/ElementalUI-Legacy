#ifndef ELEM_TEXT_FIELD_H
#define ELEM_TEXT_FIELD_H

#include <elem/elemental_ui.h>
#include <vector>
#include <limits> 

#include <elemd/vec2.hpp>
#include <elemd/color.hpp>
#include <elemd/context.hpp>

#include "elem/node.h"

namespace elem
{
    class ELEM_API TextField : public Node
    {
    public:
        TextField();

        void add_child(Node* child) = delete;

        void emit_key_event(elemd::key_event event) override;
        void emit_char_event(elemd::char_event event) override;
        void set_state(State state) override;
        //float layout(elemd::vec2 position, float width, float height) override;
        elemd::vec2 get_minimum_dimensions(float width, float height) override;
        void paint(elemd::Context* ctx) override;

        void set_text(std::string text);
        std::string get_text();
    private:
        std::string _content;
        std::string _formated_content;

        unsigned int _cursor_pos = 0;
        float _blink_timer = 0;
    };
} // namespace elem

#endif // ELEM_TEXT_FIELD_H