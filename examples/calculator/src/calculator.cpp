#include <thread>
#include <chrono>
#include <vector>

#include <elemd/font.hpp>
#include <elem/document.h>
#include <elem/element.h>
#include <elem/heading.h>
#include <elem/node.h>

#include "solver.h"

int main(void)
{
    int WIDTH = 300;
    int HEIGHT = 330;

    elemd::WindowConfig winc = elemd::WindowConfig{ "Calculator", WIDTH, HEIGHT };
    //winc.decorated = false;
    elemd::Window* window = elemd::Window::create(winc);

    {
        elem::document doc(window);
        elemd::font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");

        elemd::color button_color = elemd::color("#374352");
        elemd::color button_color_hover = elemd::color("#526379");
        elemd::color color_light = elemd::color("#f3f4f1");
        elemd::color color_darker = elemd::color("#7a7979");

        elem::element body;
        body.id = "body";
        body.style.background_color = elemd::color("#3a4655");


        elem::node::Style button_style_hover;
        button_style_hover.background_color = button_color_hover;

        elem::node::Style button_style;
        button_style.background_color = button_color;
        button_style.padding[0] = 6;
        button_style.padding[1] = 10;
        button_style.padding[2] = 6;
        button_style.padding[3] = 10;
        button_style.margin[0] = 1;
        button_style.margin[1] = 1;
        button_style.margin[2] = 1;
        button_style.margin[3] = 1;
        button_style.width = elem::measure_value("25%");
        button_style.transition_time = 3;

        elem::element display;
        display.id = "display";
        display.style.padding[0] = 20;
        display.style.padding[2] = 20;

        elem::element keypad;
        keypad.style.padding[2] = 30;

        elem::heading solution;
        solution.set_text("");
        solution.style.color = color_light;
        solution.style.font_family = font_urbanist;
        solution.style.padding[0] = 10;
        solution.style.padding[1] = 10;
        solution.style.padding[2] = 10;
        solution.style.padding[3] = 10;
        display.add_child(&solution);


        // C    +/-     %       /
        elem::element button_c;
        button_c.style = button_style;
        button_c.hover_style = button_style_hover;


        elem::element button_plus_minus;
        button_plus_minus.style = button_style;
        button_plus_minus.hover_style = button_style_hover;

        elem::element button_percent;
        button_percent.style = button_style;
        button_percent.hover_style = button_style_hover;

        elem::element button_div;
        button_div.style = button_style;
        button_div.hover_style = button_style_hover;

        // 7    8       9       x
        elem::element button_7;
        button_7.style = button_style;
        button_7.hover_style = button_style_hover;

        elem::element button_8;
        button_8.style = button_style;
        button_8.hover_style = button_style_hover;

        elem::element button_9;
        button_9.style = button_style;
        button_9.hover_style = button_style_hover;

        elem::element button_mul;
        button_mul.style = button_style;
        button_mul.hover_style = button_style_hover;

        // 4    5       6       -
        elem::element button_4;
        button_4.style = button_style;
        button_4.hover_style = button_style_hover;

        elem::element button_5;
        button_5.style = button_style;
        button_5.hover_style = button_style_hover;

        elem::element button_6;
        button_6.style = button_style;
        button_6.hover_style = button_style_hover;

        elem::element button_sub;
        button_sub.style = button_style;
        button_sub.hover_style = button_style_hover;

        // 1    2       3       +
        elem::element button_1;
        button_1.style = button_style;
        button_1.hover_style = button_style_hover;

        elem::element button_2;
        button_2.style = button_style;
        button_2.hover_style = button_style_hover;

        elem::element button_3;
        button_3.style = button_style;
        button_3.hover_style = button_style_hover;

        elem::element button_add;
        button_add.style = button_style;
        button_add.hover_style = button_style_hover;

        // 0    ,      <       =
        elem::element button_0;
        button_0.style = button_style;
        button_0.hover_style = button_style_hover;

        elem::element button_comma;
        button_comma.style = button_style;
        button_comma.hover_style = button_style_hover;

        elem::element button_less;
        button_less.style = button_style;
        button_less.hover_style = button_style_hover;

        elem::element button_equ;
        button_equ.style = button_style;
        button_equ.hover_style = button_style_hover;



        elem::heading h_c;
        h_c.set_text("c");
        h_c.style.color = elemd::color("#b85953");
        h_c.style.font_family = font_urbanist;
        h_c.add_click_listener([&](elem::node::click_event event) {
            solution.set_text("");
        });
        button_c.add_child(&h_c);

        elem::heading h_back;
        h_back.set_text("<");
        h_back.style.color = color_darker;
        h_back.style.font_family = font_urbanist;
        h_back.add_click_listener([&](elem::node::click_event event) {
            std::string s = solution.get_text();
            if (s.length() > 0)
            {
                solution.set_text(s.substr(0, s.size() - 1));
            }
        });
        button_plus_minus.add_child(&h_back);

        elem::heading h_percent;
        h_percent.set_text("%");
        h_percent.style.color = color_darker;
        h_percent.style.font_family = font_urbanist;
        button_percent.add_child(&h_percent);

        elem::heading h_div;
        h_div.set_text("/");
        h_div.style.color = color_darker;
        h_div.style.font_family = font_urbanist;
        h_div.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "/");
        });
        button_div.add_child(&h_div);


        elem::heading h_7;
        h_7.set_text("7");
        h_7.style.color = color_light;
        h_7.style.font_family = font_urbanist;
        h_7.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "7");
        });
        button_7.add_child(&h_7);

        elem::heading h_8;
        h_8.set_text("8");
        h_8.style.color = color_light;
        h_8.style.font_family = font_urbanist;
        h_8.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "8");
        });
        button_8.add_child(&h_8);

        elem::heading h_9;
        h_9.set_text("9");
        h_9.style.color = color_light;
        h_9.style.font_family = font_urbanist;
        h_9.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "9");
        });
        button_9.add_child(&h_9);

        elem::heading h_mul;
        h_mul.set_text("*");
        h_mul.style.color = color_darker;
        h_mul.style.font_family = font_urbanist;
        h_mul.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "*");
        });
        button_mul.add_child(&h_mul);

        // 4    5       6       -
        elem::heading h_4;
        h_4.set_text("4");
        h_4.style.color = color_light;
        h_4.style.font_family = font_urbanist;
        h_4.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "4");
        });
        button_4.add_child(&h_4);

        elem::heading h_5;
        h_5.set_text("5");
        h_5.style.color = color_light;
        h_5.style.font_family = font_urbanist;
        h_5.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "5");
        });
        button_5.add_child(&h_5);

        elem::heading h_6;
        h_6.set_text("6");
        h_6.style.color = color_light;
        h_6.style.font_family = font_urbanist;
        h_6.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "6");
        });
        button_6.add_child(&h_6);

        elem::heading h_sub;
        h_sub.set_text("-");
        h_sub.style.color = color_darker;
        h_sub.style.font_family = font_urbanist;
        h_sub.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "-");
        });
        button_sub.add_child(&h_sub);


        // 1    2       3       +
        elem::heading h_1;
        h_1.set_text("1");
        h_1.style.color = color_light;
        h_1.style.font_family = font_urbanist;        
        h_1.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "1");
        });
        button_1.add_child(&h_1);


        elem::heading h_2;
        h_2.set_text("2");
        h_2.style.color = color_light;
        h_2.style.font_family = font_urbanist;
        h_2.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "2");
        });
        button_2.add_child(&h_2);

        elem::heading h_3;
        h_3.set_text("3");
        h_3.style.color = color_light;
        h_3.style.font_family = font_urbanist;
        h_3.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "3");
        });
        button_3.add_child(&h_3);

        elem::heading h_add;
        h_add.set_text("+");
        h_add.style.color = color_darker;
        h_add.style.font_family = font_urbanist;
        h_add.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "+");
        });
        button_add.add_child(&h_add);


        // 0    ,      <       =
        elem::heading h_0;
        h_0.set_text("0");
        h_0.style.color = color_light;
        h_0.style.font_family = font_urbanist;
        h_0.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + "0");
        });
        button_0.add_child(&h_0);

        elem::heading h_comma;
        h_comma.set_text(",");
        h_comma.style.color = color_light;
        h_comma.style.font_family = font_urbanist;
        h_comma.add_click_listener([&](elem::node::click_event event) {
            solution.set_text(solution.get_text() + ".");
        });
        button_comma.add_child(&h_comma);

        elem::heading h_less;
        h_less.set_text("<");
        h_less.style.color = color_light;
        h_less.style.font_family = font_urbanist;
        button_less.add_child(&h_less);

        elem::heading h_equ;
        h_equ.set_text("=");
        h_equ.style.color = color_darker;
        h_equ.style.font_family = font_urbanist;
        h_equ.add_click_listener([&](elem::node::click_event event) {

            std::string val = std::to_string(Solver::eval(solution.get_text()));
            val.erase(val.find_last_not_of('0') + 1, std::string::npos);
            solution.set_text(val);

        });
        button_equ.add_child(&h_equ);


        elem::element row_1;
        row_1.add_child(&button_c);
        row_1.add_child(&button_plus_minus);
        row_1.add_child(&button_percent);
        row_1.add_child(&button_div);

        elem::element row_2;
        row_2.add_child(&button_7);
        row_2.add_child(&button_8);
        row_2.add_child(&button_9);
        row_2.add_child(&button_mul);

        elem::element row_3;
        row_3.add_child(&button_4);
        row_3.add_child(&button_5);
        row_3.add_child(&button_6);
        row_3.add_child(&button_sub);

        elem::element row_4;
        row_4.add_child(&button_1);
        row_4.add_child(&button_2);
        row_4.add_child(&button_3);
        row_4.add_child(&button_add);

        elem::element row_5;
        row_5.add_child(&button_0);
        row_5.add_child(&button_comma);
        row_5.add_child(&button_less);
        row_5.add_child(&button_equ);

        keypad.add_child(&row_1);
        keypad.add_child(&row_2);
        keypad.add_child(&row_3);
        keypad.add_child(&row_4);
        keypad.add_child(&row_5);




        body.add_child(&display);
        body.add_child(&keypad);

        /*
            elem::element test;
            test.style.display = elem::node::INLINE;
            test.style.padding[0] = 20;
            test.style.padding[1] = 20;
            test.style.padding[2] = 20;
            test.style.padding[3] = 20;
            test.style.background_color = elemd::color(200, 0, 0, 30);

            body.add_child(&test);
            */

        doc.add_child(&body);
        doc.run();

    }
    window->destroy();

    return 0;
}