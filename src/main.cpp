#include <elemd/window.hpp>
#include <elemd/context.hpp>

const int TARGET_POLL_FREQUENCY = 60;

int WIDTH = 470;
int HEIGHT = 500;
float target_poll_ms = 1.0f / TARGET_POLL_FREQUENCY;

double mouse_x = -100;
double mouse_y = -100;
bool mouse_click = false;



int main(void)
{
    elemd::WindowConfig winc = elemd::WindowConfig{"Painting App", WIDTH, HEIGHT};
    elemd::Window* win = elemd::Window::create(winc);
    elemd::Context* ctx = win->create_context();

    win->add_mouse_click_listener([&](elemd::mouse_button_event event) {
        if (event.button == elemd::MOUSE_BUTTON_LEFT &&
            (event.action == elemd::ACTION_PRESS || event.action == elemd::ACTION_REPEAT))
        {
            mouse_click = true;
        }
        else
        {
            mouse_click = false;
        }
    });

    win->add_mouse_move_listener([&](elemd::mouse_move_event event) {
        mouse_x = event.x;
        mouse_y = event.y;

        draw(ctx);
    });


    elemd::image* img = elemd::image::create("./elemd_res/elemd_icon.png");
    ctx->_tmp_register_image(img);

    ctx->set_clear_color({255, 255, 255});
    ctx->_tmp_prepare();

    while (win->is_running())
    {
        win->poll_events();
        std::this_thread::sleep_for(std::chrono::duration<float, std::ratio<1>>(target_poll_ms));

        ctx->fill_rect(10, 10, 20, 20);

        ctx->draw_frame();
    }

    img->destroy();
    win->destroy();

    return 0;
}