#ifndef ELEM_HEADING_H
#define ELEM_HEADING_H

#include <elem/elemental_ui.h>
#include <vector>
#include <limits> 

#include <elemd/vec2.hpp>
#include <elemd/color.hpp>
#include <elemd/context.hpp>

#include "elem/node.h"

namespace elem
{
    class ELEM_API Heading : public Node
    {
    public:
        Heading();

        void add_child(Node* child) = delete;

        //float layout(elemd::vec2 position, float width, float height) override;
        elemd::vec2 get_minimum_dimensions(float width, float height) override;
        void paint(elemd::Context* ctx) override;

        void set_text(std::string text);
        std::string get_text();
    private:
        std::string _content;
        std::string _formated_content;
    };
} // namespace elem

#endif // ELEM_HEADING_H