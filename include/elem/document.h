#ifndef ELEM_DOCUMENT_H
#define ELEM_DOCUMENT_H

#include <elem/elemental_ui.h>

#include <vector>
#include <chrono>

#include <elem/element.h>
#include <elemd/window.hpp>
#include <elemd/context.hpp>

namespace elem
{
    class ELEM_API document
    {
    public:
        float delta_time;

        document(elemd::Window* window);
        ~document();
        
        void add_child(node* child);
        node* get_root();
        void main_loop();

        void request_high_frequency();

        elemd::font* load_font(const std::string& font_file);
        elemd::image* load_image(const std::string& image);

        int get_width();
        int get_height();

        elemd::Window* get_window();

    private:
        int _width;
        int _height;

        bool _highFrequencyNext = false;

        node* _root = nullptr;

        elemd::Window* _window = nullptr;
        elemd::Context* _context = nullptr;
        
        node* _focused_node = nullptr;
        
        std::vector<elemd::font*> _fonts;
        std::vector<elemd::image*> _images;
        
        void paint();
    };
} // namespace elem

#endif // ELEM_DOCUMENT_H