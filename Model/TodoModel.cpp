#include "TodoModel.h"
#include <algorithm>

void TodoModel::setOnChanged(std::function<void(TodoEvent, int)> cb) {
    onChanged_ = std::move(cb);
}

void TodoModel::add(std::string title) {
    int id = nextId_++;
    items_.push_back({id, std::move(title), false});
    if (onChanged_) onChanged_(TodoEvent::Added, id);
}

void TodoModel::complete(int id) {
    auto it = std::find_if(items_.begin(), items_.end(),
        [id](const TodoItem& item) { return item.id == id; });
    if (it == items_.end()) return;
    it->done = true;
    if (onChanged_) onChanged_(TodoEvent::Completed, id);
}

void TodoModel::remove(int id) {
    auto it = std::find_if(items_.begin(), items_.end(),
        [id](const TodoItem& item) { return item.id == id; });
    if (it == items_.end()) return;
    items_.erase(it);
    if (onChanged_) onChanged_(TodoEvent::Deleted, id);
}

const std::vector<TodoItem>& TodoModel::items() const {
    return items_;
}
