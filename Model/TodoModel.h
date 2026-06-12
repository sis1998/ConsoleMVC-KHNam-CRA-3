#pragma once
#include "TodoItem.h"

class TodoModel {
    std::vector<TodoItem> items_;
    int nextId_ = 1;
    std::function<void(TodoEvent, int)> onChanged_;
public:
    void setOnChanged(std::function<void(TodoEvent, int)> cb);
    void add(std::string title);
    void complete(int id);
    void remove(int id);
    const std::vector<TodoItem>& items() const;
};
