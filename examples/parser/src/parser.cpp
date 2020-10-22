#include <elem/document.h>
#include <elem/element.h>
#include <elem/heading.h>

int main(void)
{
    int WIDTH = 300;
    int HEIGHT = 330;

    elemd::WindowConfig winc = elemd::WindowConfig{ "Parser", WIDTH, HEIGHT };
    elemd::Window* window = elemd::Window::create(winc);


    {
        elem::document doc(window);
        elemd::font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");

        elem::heading h1;
        h1.set_text("Das ist ein langer text");
        h1.style.margin[0] = 10;
        h1.style.margin[1] = 10;
        h1.style.margin[2] = 10;
        h1.style.margin[3] = 10;
        h1.style.padding[0] = 10;
        h1.style.padding[1] = 10;
        h1.style.padding[2] = 10;
        h1.style.padding[3] = 10;
        h1.style.font_family = font_urbanist;

        doc.add_child(&h1);

        doc.main_loop();
    }

    window->destroy();


    return 0;
}