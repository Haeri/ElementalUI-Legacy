#include <elem/document.h>
#include <elem/element.h>
#include <elem/text_field.h>


class Project {
public:
    std::string name;
    std::vector<std::string> incompleteTasks;
    std::vector<std::string> completedTasks;
    
    void addTask(std::string text) 
    {
        incompleteTasks.push_back(text);
    }

    void completeTask(int index) 
    {
        std::string t = incompleteTasks[index];
        incompleteTasks.erase(incompleteTasks.begin() + index);
        completedTasks.push_back(t);
    }

};


int main(void)
{
    int WIDTH = 800;
    int HEIGHT = 500;

    Project p1;
    p1.addTask("I have to fix my thesis");
    p1.addTask("Clean the room. Its dirty!");
    p1.addTask("Research unlimited energy");
    p1.addTask("World dominance.");
    std::vector<Project> projects;
    projects.push_back(p1);

    elemd::WindowConfig winc = elemd::WindowConfig{ "Tasker", WIDTH, HEIGHT };
    elemd::Window* window = elemd::Window::create(winc);


    // Style
    elem::node::Style task_wrapper;
  //  task_wrapper.background_color = elemd::color(90, 90, 90);
    task_wrapper.padding[0] = 10;
    task_wrapper.padding[1] = 10;
    task_wrapper.padding[2] = 10;
    task_wrapper.padding[3] = 10;
/*    task_wrapper.border_radius[0] = 6;
    task_wrapper.border_radius[1] = 6;
    task_wrapper.border_radius[2] = 6;
    task_wrapper.border_radius[3] = 6;
  */  

    {
        elem::document doc(window);
        elemd::font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");

        elem::element project_panel;
        project_panel.style.width = elem::measure_value("30%");
        project_panel.style.height = elem::measure_value("100%");
        project_panel.style.background_color = elemd::color(240, 240, 240);

        elem::element project_view;
        project_view.style.width = elem::measure_value("70%");

        for (auto task : projects[0].incompleteTasks)
        {
            elem::element* wrapper = new elem::element;
            wrapper->style = task_wrapper;

            elem::element* box = new elem::element;
            box->style.border_color = elemd::color(30, 30, 200);
            box->style.border_width = 1;
            box->style.width = elem::measure_value("30px");
            box->style.height = elem::measure_value("30px");

            elem::text_field* content = new elem::text_field;
            content->set_text(task);
            content->style.font_family = font_urbanist;
            content->style.font_size = 16;
            content->style.color = elemd::color(60, 60, 60);

            wrapper->add_child(content);
            project_view.add_child(wrapper);
        }

        for (auto task : projects[0].completedTasks)
        {
            elem::element* wrapper = new elem::element;
            wrapper->style = task_wrapper;

            elem::text_field* content = new elem::text_field;
            content->set_text(task);
            content->style.font_family = font_urbanist;
            content->style.font_size = 16;

            wrapper->add_child(content);
            project_view.add_child(wrapper);
        }

        doc.add_child(&project_panel);
        doc.add_child(&project_view);
        


        doc.main_loop();
    }

    window->destroy();


    return 0;
}