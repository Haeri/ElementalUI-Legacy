#include <elem/document.h>
#include <elem/element.h>
#include <elem/text_field.h>
#include <elem/heading.h>

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


void create_task(std::string task, elem::node* project_list, int index, elemd::font* font)
{
    elem::node::Style task_wrapper;
    //  task_wrapper.background_color = elemd::color(90, 90, 90);
    task_wrapper.padding[0] = 10;
    task_wrapper.padding[1] = 10;
    task_wrapper.padding[2] = 10;
    task_wrapper.padding[3] = 10;

    elem::element* wrapper = new elem::element;
    wrapper->id = "wrapper" + std::to_string(index);
    wrapper->style = task_wrapper;

    elem::element* box = new elem::element;
    box->id = "box" + std::to_string(index);
    box->style.display = elem::node::Display::INLINE;
    box->style.border_color = elemd::color(30, 30, 200);
    box->hover_style.background_color = elemd::color(30, 200, 30);
    box->style.border_width = 1;
    box->style.width = elem::measure_value(20, elem::measure_value::Type::PIXELS);
    box->style.height = elem::measure_value(20, elem::measure_value::Type::PIXELS);
    box->style.margin[1] = 10;

    elem::text_field* content = new elem::text_field;
    content->id = "content" + std::to_string(index);
    content->set_text(task);
    content->style.display = elem::node::Display::INLINE;
    content->style.font_family = font;
    content->style.font_size = 16;
    content->style.color = elemd::color(60, 60, 60);

    wrapper->add_child(box);
    wrapper->add_child(content);
    project_list->add_child(wrapper);

    box->add_click_listener([project_list, wrapper](elem::node::node_click_event event) mutable {
        project_list->remove_child(wrapper);
        wrapper->destroy();
    });
}


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
    //elem::node::Style task_wrapper;
  //  task_wrapper.background_color = elemd::color(90, 90, 90);
    //task_wrapper.padding[0] = 10;
    //task_wrapper.padding[1] = 10;
    //task_wrapper.padding[2] = 10;
    //task_wrapper.padding[3] = 10;
/*    task_wrapper.border_radius[0] = 6;
    task_wrapper.border_radius[1] = 6;
    task_wrapper.border_radius[2] = 6;
    task_wrapper.border_radius[3] = 6;
  */  

    {
        elem::document doc(window);
        elemd::font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");

        elem::element project_panel;
        project_panel.id = "project_panel";
        project_panel.style.width = elem::measure_value("30%");
        project_panel.style.height = elem::measure_value("100%");
        project_panel.style.background_color = elemd::color(240, 240, 240);

        elem::element project_view;
        project_view.id = "project_view";
        project_view.style.width = elem::measure_value("70%");

        elem::element* project_list = new elem::element;
        project_list->id = "project_list";

        int index = 0;
        for (auto task : projects[0].incompleteTasks)
        {
            
            create_task(task, project_list, index, font_urbanist);
            ++index;
        }

     


        project_view.add_child(project_list);

        elem::element* bottom_panel = new elem::element;
        bottom_panel->style.margin[0] = 30;

        elem::element* add_btn = new elem::element;
        add_btn->style.display = elem::node::Display::INLINE;
        add_btn->style.background_color = elemd::color(30, 30, 200);
        add_btn->style.width = elem::measure_value(20, elem::measure_value::Type::PIXELS);
        add_btn->style.height = elem::measure_value(20, elem::measure_value::Type::PIXELS);
        add_btn->style.margin[1] = 10;
        
        elem::heading* add_btn_text = new elem::heading;
        add_btn_text->set_text("+");
        add_btn_text->style.color = elemd::color("#ffffff");
        add_btn_text->style.font_size = 20;
        add_btn_text->style.font_family = font_urbanist;
        add_btn->add_child(add_btn_text);

        elem::text_field* add_text = new elem::text_field;
        add_text->style.display = elem::node::Display::INLINE;
        add_text->style.font_family = font_urbanist;
        add_text->style.font_size = 16;
        add_text->style.color = elemd::color(60, 60, 60);
        add_text->style.background_color = elemd::color(200, 200, 200);
        add_text->style.width = elem::measure_value(100, elem::measure_value::Type::PERCENT);

        bottom_panel->add_child(add_btn);
        bottom_panel->add_child(add_text);
        
        project_view.add_child(bottom_panel);

        doc.add_child(&project_panel);
        doc.add_child(&project_view);
        




        // Events
        add_btn->add_click_listener([&](elem::node::node_click_event event) {
            create_task(add_text->get_text(), project_list, index, font_urbanist);

            add_text->set_text("");
        });




        doc.main_loop();
    }

    window->destroy();


    return 0;
}