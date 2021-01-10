#include "elem/document.h"

#include <thread>

namespace elem
{
    document::document(elemd::Window* window)
    {
        _root = new element();
        _root->set_document(this);

        _width = window->get_width();

        _window = window;
        _context = _window->create_context();

        _window->add_resize_listener([&](elemd::resize_event event) {
            _width = event.width / _window->get_scale().get_x();
        });

        _window->add_mouse_move_listener([&](elemd::mouse_move_event event) {
            _root->bounds_check(elemd::vec2((float)event.x, (float)event.y));
            node::finish_hover_event();
        });

        _window->add_mouse_click_listener([&](elemd::mouse_button_event event)
        {
            if (event.action == elemd::input_action::ACTION_PRESS && event.button == elemd::mouse_button::MOUSE_BUTTON_LEFT)
            {
                node* node = _root->bounds_check(elemd::vec2((float)event.x, (float)event.y));
                node::finish_hover_event();

                if (_focused_node != nullptr)
                {
                    _focused_node->set_focus(false);
                }
                _focused_node = node;

                if (node != nullptr)
                {
                    _focused_node->set_focus(true);

                    node->emit_click_event(event);
                }
             }
        });

        _window->add_key_listener([&](elemd::key_event event) {
            if (_focused_node != nullptr)
            {
                _focused_node->emit_key_event(event);
            }
        });

        _window->add_char_listener([&](elemd::char_event event) {
            if (_focused_node != nullptr)
            {
                _focused_node->emit_char_event(event);
            }
        });
        

        _context->set_clear_color({ 0, 0, 0, 0 });
    }

    document::~document()
    {
        for (auto& font : _fonts) {
            font->destroy();
        }
        for (auto& img : _images) {
            img->destroy();
        }

        delete _root;

        _window->destroy();
    }

    void document::add_child(node* child)
    {
        _root->add_child(child);
        _root->set_document(this);
    }

    node* document::get_root()
    {
        return _root;
    }


    void document::main_loop()
    {
        for (auto& font : _fonts) {
            _context->_tmp_register_font(font);
        }
        for (auto& image : _images) {
            _context->_tmp_register_image(image);
        }

        _context->_tmp_prepare();
    
        using ms = std::chrono::duration<double, std::milli>;
        std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();

        while (_window->is_running())
        {
            std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
            delta_time = std::chrono::duration_cast<ms>(current_time - last_time).count() / 1000.0f;
            last_time = current_time;

            if (_highFrequencyNext)
            {
                _highFrequencyNext = false;
                _window->poll_events();
            }
            else
            {
                _window->wait_events();
                last_time = std::chrono::steady_clock::now();
            }

            paint();       
        }
    }

    void document::request_high_frequency()
    {
        _highFrequencyNext = true;
    }

    elemd::font* document::load_font(const std::string& font_file)
    {
        elemd::font* font = elemd::font::create(font_file);
        _fonts.push_back(font);

        return font;
    }

    elemd::image* document::load_image(const std::string& image)
    {
        elemd::image* img = elemd::image::create(image);
        _images.push_back(img);

        return img;
    }

    int document::get_width()
    {
        return _width;
    }

    int document::get_height()
    {
        return _height;
    }

    elemd::Window* document::get_window()
    {
        return _window;
    }

    void document::paint()
    {
        _height = _root->layout(elemd::vec2(0, 0), _width, _height);
        _root->paint(_context);

        _context->draw_frame();
    }
}