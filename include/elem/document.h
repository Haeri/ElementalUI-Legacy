#ifndef ELEM_DOCUMENT_HPP
#define ELEM_DOCUMENT_HPP

#include <elem/elemental_ui.h>
#include <elem/element.h>

#include <elemd/window.hpp>
#include <elemd/context.hpp>

namespace elem
{
    class ELEM_API document
    {
    public:
        document();
        ~document();
        
        void add_child(element* child);
        void run();

        int get_width();
        int get_height();

    private:
        int _width;
        int _height;

        element* _root;

        elemd::Window* _window;
        elemd::Context* _context;
        
        
        void paint();
    };
} // namespace elem

#endif // ELEM_DOCUMENT_HPP