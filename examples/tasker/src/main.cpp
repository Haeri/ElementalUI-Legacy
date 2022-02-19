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


void render_task(std::string task, elem::Node* project_list, int index, elemd::Font* font)
{
    elem::Node::Style task_wrapper;
    //  task_wrapper.background_color = elemd::color(90, 90, 90);
    task_wrapper.padding[0] = 10;
    task_wrapper.padding[1] = 10;
    task_wrapper.padding[2] = 10;
    task_wrapper.padding[3] = 10;

    elem::Element* wrapper = new elem::Element;
    wrapper->id = "wrapper" + std::to_string(index);
    wrapper->style = task_wrapper;

    elem::Element* box = new elem::Element;
    box->id = "box" + std::to_string(index);
    box->style.display = elem::Node::Display::INLINE;
    box->style.border_color = elemd::color(30, 30, 200);
    box->hover_style.background_color = elemd::color(30, 200, 30);
    box->style.border_width[0] = 1;
    box->style.width = elem::value(20, elem::value::Type::PIXELS);
    box->style.height = elem::value(20, elem::value::Type::PIXELS);
    box->style.margin[1] = 10;

    elem::TextField* content = new elem::TextField;
    content->id = "content" + std::to_string(index);
    content->set_text(task);
    content->style.display = elem::Node::Display::INLINE;
    content->style.font_family = font;
    content->style.font_size = 16;
    content->style.color = elemd::color(60, 60, 60);

    wrapper->add_child(box);
    wrapper->add_child(content);
    project_list->add_child(wrapper);

    box->add_click_listener([project_list, wrapper](elem::Node::node_click_event event) mutable {
        project_list->remove_child(wrapper);
        wrapper->destroy();
        return true;
    });
}

void render_all_tasks(Project* project, elem::Node* project_list, elemd::Font* font)
{
    int index = 0;
    for (auto& task : project->incompleteTasks)
    {
        render_task(task, project_list, index, font);
        ++index;
    }
}


int main(void)
{
    int WIDTH = 800;
    int HEIGHT = 500;

    std::vector<Project> projects;

    Project p1;
    p1.name = "ToDos For University";
    p1.addTask("I have to fix my thesis");
    p1.addTask("Clean the room. Its dirty!");
    p1.addTask("Research unlimited energy");
    p1.addTask("World dominance.");
    projects.push_back(p1);

    Project p2;
    p2.name = "Personal Tasks";
    p2.addTask("I have to fix my thesis");
    p2.addTask("I have to fix my thesis2");
    projects.push_back(p2);

    elemd::WindowConfig winc = elemd::WindowConfig{ "Tasker", WIDTH, HEIGHT };
    elemd::Window* window = elemd::Window::create(winc);


    elem::Document doc(window);
    elemd::Font* font_urbanist = doc.load_font("./res/font/Urbanist-Regular.ttf");

    doc.get_root()->style.background_color = elemd::color(255, 255, 255);

    elem::Element project_panel;
    project_panel.id = "project_panel";
    project_panel.style.width = elem::value("30%");
    project_panel.style.height = elem::value("100%");
    project_panel.style.background_color = elemd::color(240, 240, 240);
    project_panel.hover_style.background_color = elemd::color(240, 240, 240);

    elem::Element project_view;
    project_view.id = "project_view";
    project_view.style.width = elem::value("70%");

    elem::Element* project_list = new elem::Element;
    project_list->id = "project_list";

    for (auto& project : projects)
    {
        elem::Heading* project_btn = new elem::Heading;
        project_btn->set_text(project.name);
        project_btn->style.display = elem::Node::Display::BLOCK;
        project_btn->style.font_size = 16;
        project_btn->style.font_family = font_urbanist;
        project_btn->style.padding[0] = 4;
        project_btn->style.padding[1] = 4;
        project_btn->style.padding[2] = 4;
        project_btn->style.padding[3] = 4;
        project_btn->hover_style.background_color = elemd::color(255, 255, 255);


        project_btn->add_click_listener([&](elem::Node::node_click_event event) {
            render_all_tasks(&project, project_list, font_urbanist);
            return true;
            });


        project_panel.add_child(project_btn);
    }

    render_all_tasks(&projects[0], project_list, font_urbanist);


    project_view.add_child(project_list);

    elem::Element* bottom_panel = new elem::Element;
    bottom_panel->style.margin[0] = 30;

    elem::Element* add_btn = new elem::Element;
    add_btn->style.display = elem::Node::Display::INLINE;
    add_btn->style.background_color = elemd::color(30, 30, 200);
    add_btn->style.width = elem::value(20, elem::value::Type::PIXELS);
    add_btn->style.height = elem::value(20, elem::value::Type::PIXELS);
    add_btn->style.margin[1] = 10;

    elem::Heading* add_btn_text = new elem::Heading;
    add_btn_text->set_text("+");
    add_btn_text->style.color = elemd::color("#ffffff");
    add_btn_text->style.font_size = 20;
    add_btn_text->style.font_family = font_urbanist;
    add_btn->add_child(add_btn_text);

    elem::TextField* add_text = new elem::TextField;
    add_text->style.display = elem::Node::Display::INLINE;
    add_text->style.font_family = font_urbanist;
    add_text->style.font_size = 16;
    add_text->style.color = elemd::color(60, 60, 60);
    add_text->style.background_color = elemd::color(200, 200, 200);
    add_text->style.width = elem::value(100, elem::value::Type::PERCENT);

    bottom_panel->add_child(add_btn);
    bottom_panel->add_child(add_text);

    project_view.add_child(bottom_panel);

    doc.add_child(&project_panel);
    doc.add_child(&project_view);



    // Events
    add_btn->add_click_listener([&](elem::Node::node_click_event event) {
        render_task(add_text->get_text(), project_list, 0, font_urbanist);

        add_text->set_text("");
        return true;
        });


    doc.main_loop();



    return 0;
}