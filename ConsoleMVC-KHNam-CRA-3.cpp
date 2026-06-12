#include "Controller/TodoController.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TodoController controller;
    controller.run();
    return 0;
}
