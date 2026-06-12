#pragma once
#include "../Model/TodoModel.h"
#include "../View/TodoView.h"

class TodoController {
    TodoModel model_;
    TodoView  view_;
public:
    TodoController();
    void run();
private:
    void handleInput(std::string_view line);
    void onModelChanged(TodoEvent event, int id);
};
