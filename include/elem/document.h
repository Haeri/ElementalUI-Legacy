#ifndef ELEM_DOCUMENT_H
#define ELEM_DOCUMENT_H

#include <elem/elemental_ui.h>

#include <vector>

#include <elem/element.h>
#include <elemd/window.hpp>
#include <elemd/context.hpp>

namespace elem
{
    class ELEM_API document
    {
    public:
        document(elemd::Window* window);
        ~document();
        
        void add_child(node* child);
        void main_loop();

        elemd::font* load_font(const std::string& font_file);

        int get_width();
        int get_height();

    private:
        int _width;
        int _height;

        node* _root;

        elemd::Window* _window;
        elemd::Context* _context;
        
        std::vector<elemd::font*> _fonts;
        
        void paint();
    };
} // namespace elem

#endif // ELEM_DOCUMENT_H