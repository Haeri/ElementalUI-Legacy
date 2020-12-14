#ifndef ELEM_ELEMENT_H
#define ELEM_ELEMENT_H

#include <elem/elemental_ui.h>
#include <vector>
#include <limits> 

#include <elemd/vec2.hpp>
#include <elemd/color.hpp>
#include <elemd/context.hpp>

#include "elem/node.h"

namespace elem
{
    class ELEM_API element : public node
    {
    public:

        //float layout(elemd::vec2 position, float width, float height) override;
        void paint(elemd::Context* ctx) override;
    
    };
} // namespace elem

#endif // ELEM_ELEMENT_H