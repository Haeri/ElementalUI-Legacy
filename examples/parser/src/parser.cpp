#include <elem/document.h>
#include <elem/element.h>

int main(void)
{
    int WIDTH = 300;
    int HEIGHT = 330;

    elemd::WindowConfig winc = elemd::WindowConfig{ "Parser", WIDTH, HEIGHT };
    elemd::Window* window = elemd::Window::create(winc);

    {
        elem::document doc(window);
        doc.run();
    }

    window->destroy();


    return 0;
}