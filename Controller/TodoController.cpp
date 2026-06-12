#include "TodoController.h"
#include <iostream>
#include <sstream>
#include <string>

TodoController::TodoController() {
    model_.setOnChanged([this](TodoEvent event, int id) {
        onModelChanged(event, id);
    });
}

void TodoController::run() {
    view_.renderList(model_.items());
    view_.renderMessage("명령어: add <제목> | done <id> | del <id> | quit");

    std::string line;
    while (true) {
        view_.renderPrompt();
        if (!std::getline(std::cin, line)) break;
        if (line == "quit") break;
        handleInput(line);
    }
}

void TodoController::handleInput(std::string_view line) {
    std::istringstream ss{std::string{line}};
    std::string cmd;
    ss >> cmd;

    if (cmd == "add") {
        std::string title;
        std::getline(ss >> std::ws, title);
        if (title.empty()) {
            view_.renderMessage("오류: 제목을 입력하세요. 예) add 장보기");
            return;
        }
        model_.add(std::move(title));
    } else if (cmd == "done") {
        int id{};
        if (!(ss >> id)) {
            view_.renderMessage("오류: id를 입력하세요. 예) done 1");
            return;
        }
        model_.complete(id);
    } else if (cmd == "del") {
        int id{};
        if (!(ss >> id)) {
            view_.renderMessage("오류: id를 입력하세요. 예) del 1");
            return;
        }
        model_.remove(id);
    } else {
        view_.renderMessage("알 수 없는 명령어. 사용 가능: add | done | del | quit");
    }
}

void TodoController::onModelChanged(TodoEvent /*event*/, int /*id*/) {
    view_.renderList(model_.items());
}
