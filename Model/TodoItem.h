#pragma once
#include <string>
#include <functional>
#include <vector>

struct TodoItem {
    int id;
    std::string title;
    bool done = false;
};

enum class TodoEvent { Added, Completed, Deleted };
