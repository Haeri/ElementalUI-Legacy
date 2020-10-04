#include "..\include\elem\document.h"

#include <thread>

elem::document::document()
{
    _root = new element();

    int WIDTH = 470;
    int HEIGHT = 500;
    _width = 470;

    elemd::WindowConfig winc = elemd::WindowConfig{ "Elemental UI", WIDTH, HEIGHT };
    _window = elemd::Window::create(winc);
    _context = _window->create_context();

    _window->add_resize_listener([&](elemd::resize_event event) {
        _width = event.width / _window->get_scale().get_x();
    });

    _context->set_clear_color({ 255, 255, 255 });
    _context->_tmp_prepare();
}

elem::document::~document()
{
    delete _root;
    _window->destroy();
}

void elem::document::add_child(element* child)
{
    _root->add_child(child);
}

void elem::document::run()
{
    while (_window->is_running())
    {
        _window->poll_events();
        std::this_thread::sleep_for(std::chrono::duration<float, std::ratio<1>>(0.06f));

        paint();
    }
}

int elem::document::get_width()
{
    return _width;
}

int elem::document::get_height()
{
    return _height;
}

void elem::document::paint()
{
    _height = _root->layout(elemd::vec2(0, 0), _width);
    _root->paint(_context);

    _context->draw_frame();
}
