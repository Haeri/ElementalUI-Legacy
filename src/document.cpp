#include "elem/document.h"

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
            node::finish_hover_event();
        });

        _window->add_mouse_click_listener([&](elemd::mouse_button_event event)
        {
            if (event.action == elemd::input_action::ACTION_PRESS && event.button == elemd::mouse_button::MOUSE_BUTTON_LEFT)
            {
                node* node = _root->bounds_check(elemd::vec2((float)event.x, (float)event.y));
                node::finish_hover_event();

                if (node != nullptr)
                {
                    node->emit_click_event(event);
                }
            }
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

    void document::main_loop()
    {
        for (auto& font : _fonts) {
            _context->_tmp_register_font(font);
        }

        _context->_tmp_prepare();
    
        using ms = std::chrono::duration<double, std::milli>;
        std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();

        while (_window->is_running())
        {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            _context->set_clear_color(elemd::color("#f3f4f1"));


            if (std::chrono::duration_cast<ms>(_highFrequencyTill - begin).count() > 0)
            {
                _window->wait_events(0.03f);
                std::cout << "FAST" << std::endl;
            }
            else
            {
                _window->wait_events(0.03f);
                //_window->wait_events();
                std::cout << "SLOW" << std::endl;
            }

            //std::cout << "RUNNING" << std::endl;

            paint();
        }
    }

    void document::request_high_frequency(float timestamp)
    {
        _highFrequencyTill += std::chrono::milliseconds((int)timestamp * 1000);
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