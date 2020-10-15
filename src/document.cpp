#include "..\include\elem\document.h"

#include <thread>

namespace elem
{
    document::document(elemd::Window* window)
    {
        _root = new element();

        _width = window->get_width();

        _window = window;
        _context = _window->create_context();

        _window->add_resize_listener([&](elemd::resize_event event) {
            _width = event.width / _window->get_scale().get_x();
        });

        _window->add_mouse_move_listener([&](elemd::mouse_move_event event) {            
            _root->bounds_check(elemd::vec2((float)event.x, (float)event.y));
        });

        _context->set_clear_color({ 255, 255, 255 });
    }

    document::~document()
    {
        for (auto& font : _fonts) {
            font->destroy();
        }

        delete _root;
    }

    void document::add_child(node* child)
    {
        _root->add_child(child);
    }

    void document::run()
    {
        for (auto& font : _fonts) {
            _context->_tmp_register_font(font);
        }

        _context->_tmp_prepare();
    
        while (_window->is_running())
        {
        _context->set_clear_color(elemd::color("#f3f4f1"));
            _window->poll_events();
            std::this_thread::sleep_for(std::chrono::duration<float, std::ratio<1>>(0.06f));

            paint();
        }
    }

    elemd::font* document::load_font(const std::string& font_file)
    {
        elemd::font* font = elemd::font::create(font_file);
        _fonts.push_back(font);

        return font;
    }

    int document::get_width()
    {
        return _width;
    }

    int document::get_height()
    {
        return _height;
    }

    void document::paint()
    {
        _height = _root->layout(elemd::vec2(0, 0), _width);
        _root->paint(_context);

        _context->draw_frame();
    }
}