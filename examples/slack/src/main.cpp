#include <elem/document.h>
#include <elem/element.h>
#include <elem/heading.h>

int main(void)
{
    int WIDTH = 1920 / 2;
    int HEIGHT = 1248 / 2;

    bool move_drag = false;
    bool maximized = false;

    float mouse_to_window_delta_x = 0;
    float mouse_to_window_delta_y = 0;

    /* --------------- Colors --------------- */

    elemd::color title_dark = elemd::color("#171b21");
    elemd::color sidebar_blue = elemd::color("#1d2229");
    elemd::color select_green = elemd::color("#4f9588");

    elemd::color title_red = elemd::color("#ff6059");
    elemd::color title_yellow = elemd::color("#ffbe2f");
    elemd::color title_green = elemd::color("#2aca41");

    elemd::color status_green = elemd::color("#2bac76");


    elemd::WindowConfig winc = elemd::WindowConfig{ "Slack", WIDTH, HEIGHT };
    winc.decorated = false;
    winc.transparent = true;
    elemd::Window* window = elemd::Window::create(winc);


    /* --------------- Events --------------- */

    window->add_mouse_move_listener([&](elemd::mouse_move_event event)
        {
            if (move_drag)
            {
                elemd::vec2 pos = window->get_position();
                window->set_position(pos.get_x() + event.x - mouse_to_window_delta_x, pos.get_y() + event.y - mouse_to_window_delta_y);
            }
        }
    );

    window->add_mouse_click_listener([&](elemd::mouse_button_event event)
        {
            if (move_drag && event.action == elemd::ACTION_RELEASE)
            {
                move_drag = false;
            }
        }
    );


    elem::document doc(window);
    elemd::image* _template = doc.load_image("./res/template.png");
    elemd::font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");

    elem::node* root = doc.get_root();

    //root->style.background_image = _template;
    root->style.width.set_pixels(WIDTH);
    root->style.height.set_pixels(HEIGHT);


    elem::element title_bar;
    title_bar.id = "title_bar";
    title_bar.style.background_color = title_dark;
    title_bar.style.padding[0] = 8;
    title_bar.style.padding[1] = 6;
    title_bar.style.padding[2] = 8;
    title_bar.style.padding[3] = 6;
    title_bar.style.border_radius[3] = 6;
    title_bar.style.border_radius[1] = 6;
    title_bar.add_click_listener([&](elem::node::node_click_event event)
        {
            mouse_to_window_delta_x = event.event.x;
            mouse_to_window_delta_y = event.event.y;
            move_drag = true;
            return true;
        }
    );

    elem::element close_btn;
    close_btn.style.display = elem::node::INLINE;
    close_btn.style.background_color = title_red;
    close_btn.style.padding[0] = 6;
    close_btn.style.padding[1] = 6;
    close_btn.style.padding[2] = 6;
    close_btn.style.padding[3] = 6;
    close_btn.style.margin[0] = 4;
    close_btn.style.margin[1] = 4;
    close_btn.style.margin[2] = 4;
    close_btn.style.margin[3] = 4;
    close_btn.style.border_radius[0] = 6;
    close_btn.style.border_radius[1] = 6;
    close_btn.style.border_radius[2] = 6;
    close_btn.style.border_radius[3] = 6;
    close_btn.hover_style = close_btn.style;
    close_btn.hover_style.background_color = elemd::color("#ff726b");
    close_btn.style.transition_time = 0.2f;
    close_btn.add_click_listener([&](elem::node::node_click_event event)
        {
            window->close();
            return false;
        }
    );


    elem::element min_btn;
    min_btn.style.display = elem::node::INLINE;
    min_btn.style.background_color = title_green;
    min_btn.style.padding[0] = 6;
    min_btn.style.padding[1] = 6;
    min_btn.style.padding[2] = 6;
    min_btn.style.padding[3] = 6;
    min_btn.style.margin[0] = 4;
    min_btn.style.margin[1] = 4;
    min_btn.style.margin[2] = 4;
    min_btn.style.margin[3] = 4;
    min_btn.style.border_radius[0] = 6;
    min_btn.style.border_radius[1] = 6;
    min_btn.style.border_radius[2] = 6;
    min_btn.style.border_radius[3] = 6;
    min_btn.hover_style = min_btn.style;
    min_btn.hover_style.background_color = elemd::color("#5ddf71");
    min_btn.style.transition_time = 0.2f;
    min_btn.add_click_listener([&](elem::node::node_click_event event)
        {
            move_drag = false;
            window->minimize();
            return false;
        }
    );

    elem::element max_btn;
    max_btn.style.display = elem::node::INLINE;
    max_btn.style.background_color = title_yellow;
    max_btn.style.padding[0] = 6;
    max_btn.style.padding[1] = 6;
    max_btn.style.padding[2] = 6;
    max_btn.style.padding[3] = 6;
    max_btn.style.margin[0] = 4;
    max_btn.style.margin[1] = 4;
    max_btn.style.margin[2] = 4;
    max_btn.style.margin[3] = 4;
    max_btn.style.border_radius[0] = 6;
    max_btn.style.border_radius[1] = 6;
    max_btn.style.border_radius[2] = 6;
    max_btn.style.border_radius[3] = 6;
    max_btn.hover_style = max_btn.style;
    max_btn.hover_style.background_color = elemd::color("#ffdf3d");
    max_btn.style.transition_time = 0.2f;
    max_btn.add_click_listener([&](elem::node::node_click_event event)
        {
            if (!maximized)
            {
                window->maximize();
            }
            else
            {
                window->restore();
            }

            maximized = !maximized;
            return false;
        }
    );



    title_bar.add_child(&close_btn);
    title_bar.add_child(&max_btn);
    title_bar.add_child(&min_btn);

    elem::element body;
    body.id = "body";

    elem::element sidebar;
    sidebar.id = "sidebar";
    sidebar.style.background_color = sidebar_blue;
    sidebar.style.width.set_percent(23);
    sidebar.style.height.set_pixels(HEIGHT - 40);
    body.add_child(&sidebar);


    elem::element body_content;
    body_content.id = "body_content";
    body_content.style.background_color = elemd::color(255, 255, 255);
    body_content.style.width.set_percent(77);
    body_content.style.height.set_pixels(HEIGHT - 40);
    body.add_child(&body_content);




    doc.add_child(&title_bar);
    doc.add_child(&body);

    doc.main_loop();


    return 0;
}