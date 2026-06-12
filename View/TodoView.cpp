#include "TodoView.h"
#include <iostream>
#include <format>

void TodoView::renderList(const std::vector<TodoItem>& items) {
    std::cout << "\n--- Todo 목록 (" << items.size() << "건) ---\n";
    if (items.empty()) {
        std::cout << "  (비어 있음)\n";
    } else {
        for (const auto& item : items) {
            std::cout << std::format("  [{}] {}. {}\n",
                item.done ? 'x' : ' ',
                item.id,
                item.title);
        }
    }
    std::cout << "-------------------------\n";
}

void TodoView::renderMessage(std::string_view msg) {
    std::cout << msg << '\n';
}

void TodoView::renderPrompt() {
    std::cout << "> " << std::flush;
}
