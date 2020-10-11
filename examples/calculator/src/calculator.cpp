#include <thread>
#include <chrono>
#include <vector>

#include <elemd/font.hpp>
#include <elem/document.h>
#include <elem/element.h>
#include <elem/heading.h>

int main(void)
{
    elem::document doc;
    elemd::font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");


    elemd::color button_color = elemd::color("#374352");
    elemd::color color_light = elemd::color("#f3f4f1");
    elemd::color color_darker = elemd::color("#7a7979");
    



    elem::element body;
    body.style.background_color = elemd::color("#3a4655");


    elem::element display;

    elem::element keypad;
    
    // C    +/-     %       /
    elem::element button_c;
    button_c.style.background_color = button_color;
    button_c.style.padding[0] = 6;
    button_c.style.padding[1] = 10;
    button_c.style.padding[2] = 6;
    button_c.style.padding[3] = 10;
    button_c.style.margin[0] = 1;
    button_c.style.margin[1] = 1;
    button_c.style.margin[2] = 1;
    button_c.style.margin[3] = 1;
    button_c.style.width = elem::measure_value("25%");

    elem::element button_plus_minus;
    button_plus_minus.style.background_color = button_color;
    button_plus_minus.style.padding[0] = 6;
    button_plus_minus.style.padding[1] = 10;
    button_plus_minus.style.padding[2] = 6;
    button_plus_minus.style.padding[3] = 10;
    button_plus_minus.style.margin[0] = 1;
    button_plus_minus.style.margin[1] = 1;
    button_plus_minus.style.margin[2] = 1;
    button_plus_minus.style.margin[3] = 1;
    button_plus_minus.style.width = elem::measure_value("25%");

    elem::element button_percent;
    button_percent.style.background_color = button_color;
    button_percent.style.padding[0] = 6;
    button_percent.style.padding[1] = 10;
    button_percent.style.padding[2] = 6;
    button_percent.style.padding[3] = 10;
    button_percent.style.margin[0] = 1;
    button_percent.style.margin[1] = 1;
    button_percent.style.margin[2] = 1;
    button_percent.style.margin[3] = 1;
    button_percent.style.width = elem::measure_value("25%");

    elem::element button_div;
    button_div.style.background_color = button_color;
    button_div.style.padding[0] = 6;
    button_div.style.padding[1] = 10;
    button_div.style.padding[2] = 6;
    button_div.style.padding[3] = 10;
    button_div.style.margin[0] = 1;
    button_div.style.margin[1] = 1;
    button_div.style.margin[2] = 1;
    button_div.style.margin[3] = 1;
    button_div.style.width = elem::measure_value("25%");

    // 7    8       9       x
    elem::element button_7;
    button_7.style.background_color = button_color;
    button_7.style.padding[0] = 6;
    button_7.style.padding[1] = 10;
    button_7.style.padding[2] = 6;
    button_7.style.padding[3] = 10;
    button_7.style.margin[0] = 1;
    button_7.style.margin[1] = 1;
    button_7.style.margin[2] = 1;
    button_7.style.margin[3] = 1;
    button_7.style.width = elem::measure_value("25%");

    elem::element button_8;
    button_8.style.background_color = button_color;
    button_8.style.padding[0] = 6;
    button_8.style.padding[1] = 10;
    button_8.style.padding[2] = 6;
    button_8.style.padding[3] = 10;
    button_8.style.margin[0] = 1;
    button_8.style.margin[1] = 1;
    button_8.style.margin[2] = 1;
    button_8.style.margin[3] = 1;
    button_8.style.width = elem::measure_value("25%");

    elem::element button_9;
    button_9.style.background_color = button_color;
    button_9.style.padding[0] = 6;
    button_9.style.padding[1] = 10;
    button_9.style.padding[2] = 6;
    button_9.style.padding[3] = 10;
    button_9.style.margin[0] = 1;
    button_9.style.margin[1] = 1;
    button_9.style.margin[2] = 1;
    button_9.style.margin[3] = 1;
    button_9.style.width = elem::measure_value("25%");

    elem::element button_mul;
    button_mul.style.background_color = button_color;
    button_mul.style.padding[0] = 6;
    button_mul.style.padding[1] = 10;
    button_mul.style.padding[2] = 6;
    button_mul.style.padding[3] = 10;
    button_mul.style.margin[0] = 1;
    button_mul.style.margin[1] = 1;
    button_mul.style.margin[2] = 1;
    button_mul.style.margin[3] = 1;
    button_mul.style.width = elem::measure_value("25%");

    // 4    5       6       -
    elem::element button_4;
    button_4.style.background_color = button_color;
    button_4.style.padding[0] = 6;
    button_4.style.padding[1] = 10;
    button_4.style.padding[2] = 6;
    button_4.style.padding[3] = 10;
    button_4.style.margin[0] = 1;
    button_4.style.margin[1] = 1;
    button_4.style.margin[2] = 1;
    button_4.style.margin[3] = 1;
    button_4.style.width = elem::measure_value("25%");

    elem::element button_5;
    button_5.style.background_color = button_color;
    button_5.style.padding[0] = 6;
    button_5.style.padding[1] = 10;
    button_5.style.padding[2] = 6;
    button_5.style.padding[3] = 10;
    button_5.style.margin[0] = 1;
    button_5.style.margin[1] = 1;
    button_5.style.margin[2] = 1;
    button_5.style.margin[3] = 1;
    button_5.style.width = elem::measure_value("25%");

    elem::element button_6;
    button_6.style.background_color = button_color;
    button_6.style.padding[0] = 6;
    button_6.style.padding[1] = 10;
    button_6.style.padding[2] = 6;
    button_6.style.padding[3] = 10;
    button_6.style.margin[0] = 1;
    button_6.style.margin[1] = 1;
    button_6.style.margin[2] = 1;
    button_6.style.margin[3] = 1;
    button_6.style.width = elem::measure_value("25%");

    elem::element button_sub;
    button_sub.style.background_color = button_color;
    button_sub.style.padding[0] = 6;
    button_sub.style.padding[1] = 10;
    button_sub.style.padding[2] = 6;
    button_sub.style.padding[3] = 10;
    button_sub.style.margin[0] = 1;
    button_sub.style.margin[1] = 1;
    button_sub.style.margin[2] = 1;
    button_sub.style.margin[3] = 1;
    button_sub.style.width = elem::measure_value("25%");

    // 1    2       3       +
    elem::element button_1;
    button_1.style.background_color = button_color;
    button_1.style.padding[0] = 6;
    button_1.style.padding[1] = 10;
    button_1.style.padding[2] = 6;
    button_1.style.padding[3] = 10;
    button_1.style.margin[0] = 1;
    button_1.style.margin[1] = 1;
    button_1.style.margin[2] = 1;
    button_1.style.margin[3] = 1;
    button_1.style.width = elem::measure_value("25%");

    elem::element button_2;
    button_2.style.background_color = button_color;
    button_2.style.padding[0] = 6;
    button_2.style.padding[1] = 10;
    button_2.style.padding[2] = 6;
    button_2.style.padding[3] = 10;
    button_2.style.margin[0] = 1;
    button_2.style.margin[1] = 1;
    button_2.style.margin[2] = 1;
    button_2.style.margin[3] = 1;
    button_2.style.width = elem::measure_value("25%");

    elem::element button_3;
    button_3.style.background_color = button_color;
    button_3.style.padding[0] = 6;
    button_3.style.padding[1] = 10;
    button_3.style.padding[2] = 6;
    button_3.style.padding[3] = 10;
    button_3.style.margin[0] = 1;
    button_3.style.margin[1] = 1;
    button_3.style.margin[2] = 1;
    button_3.style.margin[3] = 1;
    button_3.style.width = elem::measure_value("25%");

    elem::element button_add;
    button_add.style.background_color = button_color;
    button_add.style.padding[0] = 6;
    button_add.style.padding[1] = 10;
    button_add.style.padding[2] = 6;
    button_add.style.padding[3] = 10;
    button_add.style.margin[0] = 1;
    button_add.style.margin[1] = 1;
    button_add.style.margin[2] = 1;
    button_add.style.margin[3] = 1;
    button_add.style.width = elem::measure_value("25%");

    // 0    ,      <       =
    elem::element button_0;
    button_0.style.background_color = button_color;
    button_0.style.padding[0] = 6;
    button_0.style.padding[1] = 10;
    button_0.style.padding[2] = 6;
    button_0.style.padding[3] = 10;
    button_0.style.margin[0] = 1;
    button_0.style.margin[1] = 1;
    button_0.style.margin[2] = 1;
    button_0.style.margin[3] = 1;
    button_0.style.width = elem::measure_value("25%");

    elem::element button_comma;
    button_comma.style.background_color = button_color;
    button_comma.style.padding[0] = 6;
    button_comma.style.padding[1] = 10;
    button_comma.style.padding[2] = 6;
    button_comma.style.padding[3] = 10;
    button_comma.style.margin[0] = 1;
    button_comma.style.margin[1] = 1;
    button_comma.style.margin[2] = 1;
    button_comma.style.margin[3] = 1;
    button_comma.style.width = elem::measure_value("25%");

    elem::element button_less;
    button_less.style.background_color = button_color;
    button_less.style.padding[0] = 6;
    button_less.style.padding[1] = 10;
    button_less.style.padding[2] = 6;
    button_less.style.padding[3] = 10;
    button_less.style.margin[0] = 1;
    button_less.style.margin[1] = 1;
    button_less.style.margin[2] = 1;
    button_less.style.margin[3] = 1;
    button_less.style.width = elem::measure_value("25%");

    elem::element button_equ;
    button_equ.style.background_color = button_color;
    button_equ.style.padding[0] = 6;
    button_equ.style.padding[1] = 10;
    button_equ.style.padding[2] = 6;
    button_equ.style.padding[3] = 10;
    button_equ.style.margin[0] = 1;
    button_equ.style.margin[1] = 1;
    button_equ.style.margin[2] = 1;
    button_equ.style.margin[3] = 1;
    button_equ.style.width = elem::measure_value("25%");


    
    elem::heading h_c;
    h_c.set_text("c");
    h_c.style.color = elemd::color("#b85953");
    h_c.style.font_family = font_urbanist;
    button_c.add_child(&h_c);

    elem::heading h_plus_minus;
    h_plus_minus.set_text("+/-");
    h_plus_minus.style.color = color_darker;
    h_plus_minus.style.font_family = font_urbanist;
    button_plus_minus.add_child(&h_plus_minus);

    elem::heading h_percent;
    h_percent.set_text("%");
    h_percent.style.color = color_darker;
    h_percent.style.font_family = font_urbanist;
    button_percent.add_child(&h_percent);

    elem::heading h_div;
    h_div.set_text("/");
    h_div.style.color = color_darker;
    h_div.style.font_family = font_urbanist;
    button_div.add_child(&h_div);

    
    elem::heading h_7;
    h_7.set_text("7");
    h_7.style.color = color_light;
    h_7.style.font_family = font_urbanist;
    button_7.add_child(&h_7);

    elem::heading h_8;
    h_8.set_text("8");
    h_8.style.color = color_light;
    h_8.style.font_family = font_urbanist;
    button_8.add_child(&h_8);

    elem::heading h_9;
    h_9.set_text("9");
    h_9.style.color = color_light;
    h_9.style.font_family = font_urbanist;
    button_9.add_child(&h_9);

    elem::heading h_mul;
    h_mul.set_text("*");
    h_mul.style.color = color_darker;
    h_mul.style.font_family = font_urbanist;
    button_mul.add_child(&h_mul);

    // 4    5       6       -
    elem::heading h_4;
    h_4.set_text("4");
    h_4.style.color = color_light;
    h_4.style.font_family = font_urbanist;
    button_4.add_child(&h_4);

    elem::heading h_5;
    h_5.set_text("5");
    h_5.style.color = color_light;
    h_5.style.font_family = font_urbanist;
    button_5.add_child(&h_5);

    elem::heading h_6;
    h_6.set_text("6");
    h_6.style.color = color_light;
    h_6.style.font_family = font_urbanist;
    button_6.add_child(&h_6);

    elem::heading h_sub;
    h_sub.set_text("-");
    h_sub.style.color = color_darker;
    h_sub.style.font_family = font_urbanist;
    button_sub.add_child(&h_sub);


    // 1    2       3       +
    elem::heading h_1;
    h_1.set_text("1");
    h_1.style.color = color_light;
    h_1.style.font_family = font_urbanist;
    button_1.add_child(&h_1);

    elem::heading h_2;
    h_2.set_text("2");
    h_2.style.color = color_light;
    h_2.style.font_family = font_urbanist;
    button_2.add_child(&h_2);

    elem::heading h_3;
    h_3.set_text("3");
    h_3.style.color = color_light;
    h_3.style.font_family = font_urbanist;
    button_3.add_child(&h_3);

    elem::heading h_add;
    h_add.set_text("+");
    h_add.style.color = color_darker;
    h_add.style.font_family = font_urbanist;
    button_add.add_child(&h_add);


    // 0    ,      <       =
    elem::heading h_0;
    h_0.set_text("0");
    h_0.style.color = color_light;
    h_0.style.font_family = font_urbanist;
    button_0.add_child(&h_0);

    elem::heading h_comma;
    h_comma.set_text(",");
    h_comma.style.color = color_light;
    h_comma.style.font_family = font_urbanist;
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



    elem::heading solution;
    solution.set_text("12990");
    solution.style.color = color_light;
    solution.style.font_family = font_urbanist;
    solution.style.padding[0] = 10;
    solution.style.padding[1] = 10;
    solution.style.padding[2] = 10;
    solution.style.padding[3] = 10;
    display.add_child(&solution);


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

    return 0;
}