#ifndef ELEM_ELEMX_PARSER_HPP
#define ELEM_ELEMX_PARSER_HPP

#include <unordered_map>

#include "elem/elemental_ui.h"
#include "elem/element.h"

namespace elem
{
    class ELEM_API elemx_parser
    {
        std::unordered_map<std::string, element*> KEYWORDS = 
        {
//            {"elem", }
        };


        static element* parse(const std::string& file_path);
    };
}

#endif // ELEM_ELEMX_PARSER_HPP