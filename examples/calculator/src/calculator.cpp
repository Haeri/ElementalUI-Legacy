#include <thread>
#include <chrono>
#include <vector>

#include <elem/document.h>
#include <elem/element.h>

int main(void)
{
    elem::element button;
    button.style.padding[0] = 10;
    button.style.padding[1] = 10;
    button.style.padding[2] = 10;
    button.style.padding[3] = 10;

    button.style.margin[0] = 10;
    button.style.margin[1] = 20;
    button.style.margin[2] = 10;
    button.style.margin[3] = 20;
    
    button.style.display = elem::element::Display::INLINE;
    button.style.background_color = elemd::color("#f4ebc1");



    elem::element button2;
    button2.style.padding[0] = 10;
    button2.style.padding[1] = 10;
    button2.style.padding[2] = 10;
    button2.style.padding[3] = 10;
          
    button2.style.margin[0] = 10;
    button2.style.margin[1] = 20;
    button2.style.margin[2] = 10;
    button2.style.margin[3] = 20;

    button2.style.display = elem::element::Display::INLINE;
    button2.style.background_color = elemd::color("#de4463");

    elem::element button3;
    button3.style.padding[0] = 10;
    button3.style.padding[1] = 10;
    button3.style.padding[2] = 10;
    button3.style.padding[3] = 10;
          
    button3.style.margin[0] = 10;
    button3.style.margin[1] = 20;
    button3.style.margin[2] = 10;
    button3.style.margin[3] = 20;
          
    button3.style.display = elem::element::Display::INLINE;
    button3.style.background_color = elemd::color("#f4ebc1");


    elem::element button4;
    button4.style.padding[0] = 10;
    button4.style.padding[1] = 10;
    button4.style.padding[2] = 10;
    button4.style.padding[3] = 10;
          
    button4.style.margin[0] = 20;
    button4.style.margin[1] = 10;
    button4.style.margin[2] = 20;
    button4.style.margin[3] = 10;
          
//    button4.style.display = elem::element::Display::INLINE;
    button4.style.background_color = elemd::color("#de4463");



    elem::element button_wrapper;
    button_wrapper.style.padding[0] = 100;
    button_wrapper.style.padding[1] = 100;
    button_wrapper.style.padding[2] = 100;
    button_wrapper.style.padding[3] = 100;

    button_wrapper.style.background_color = elemd::color("#709fb0");
    button_wrapper.add_child(&button);
    button_wrapper.add_child(&button2);
    button_wrapper.add_child(&button3);
    button_wrapper.add_child(&button4);

    elem::document doc;
    doc.add_child(&button_wrapper);

    doc.run();



    return 0;
}