#pragma once
#include <vector>
#include <string_view>
#include "../Model/TodoItem.h"

class TodoView {
public:
    void renderList(const std::vector<TodoItem>& items);
    void renderMessage(std::string_view msg);
    void renderPrompt();
};
