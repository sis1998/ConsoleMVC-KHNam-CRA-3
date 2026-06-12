# Todo MVC PoC 설계

**날짜:** 2026-06-12  
**프로젝트:** ConsoleMVC-KHNam-CRA-3  
**목표:** C++20 콘솔 앱에서 MVC 레이어 분리 PoC. Model/View/Controller 역할 경계를 코드로 증명한다.

---

## 1. 파일 구조

```
ConsoleMVC-KHNam-CRA-3/
├── Model/
│   ├── TodoItem.h              # 데이터 구조체
│   ├── TodoModel.h
│   └── TodoModel.cpp
├── View/
│   ├── TodoView.h
│   └── TodoView.cpp
├── Controller/
│   ├── TodoController.h
│   └── TodoController.cpp
└── ConsoleMVC-KHNam-CRA-3.cpp  # main()
```

새 소스 파일은 모두 `.vcxproj` 의 `<ItemGroup>` 에 `<ClCompile>` 항목을 함께 추가한다.

---

## 2. 레이어 경계 규칙

| 레이어 | std::cout | std::cin | Model 참조 | View 참조 |
|--------|-----------|----------|------------|-----------|
| Model | 금지 | 금지 | — | 금지 |
| View | 허용 | 금지 | 금지 | — |
| Controller | 금지 | 허용 | 허용 | 허용 |

---

## 3. Model

### TodoItem (구조체)

```cpp
struct TodoItem {
    int id;
    std::string title;
    bool done = false;
};
```

### TodoEvent (열거형)

```cpp
enum class TodoEvent { Added, Completed, Deleted };
```

### TodoModel

```cpp
class TodoModel {
    std::vector<TodoItem> items_;
    int nextId_ = 1;
    std::function<void(TodoEvent, int)> onChanged_;
public:
    void setOnChanged(std::function<void(TodoEvent, int)> cb);
    void add(std::string title);      // Added 이벤트 발행
    void complete(int id);            // Completed 이벤트 발행, id 없으면 무시
    void remove(int id);              // Deleted 이벤트 발행, id 없으면 무시
    const std::vector<TodoItem>& items() const;
};
```

변경 즉시 `onChanged_(event, id)` 호출. 콜백 미등록 시 무시.

---

## 4. View

```cpp
class TodoView {
public:
    void renderList(const std::vector<TodoItem>& items);
    void renderMessage(std::string_view msg);
    void renderPrompt();  // "> " 출력 (줄바꿈 없음)
};
```

- `renderList`: 번호, 완료 표시(`[x]`/`[ ]`), 제목 출력
- `renderMessage`: 오류/안내 메시지 출력
- Model을 직접 참조하지 않는다.

---

## 5. Controller

```cpp
class TodoController {
    TodoModel model_;
    TodoView  view_;
public:
    void run();
private:
    void handleInput(std::string_view line);
    void onModelChanged(TodoEvent event, int id);
};
```

### run() 흐름

```
생성자에서 model_.setOnChanged(onModelChanged 바인딩)
view_.renderList(model_.items())  ← 초기 목록 표시
loop:
    view_.renderPrompt()
    getline(std::cin, line)
    if (line == "quit") break
    handleInput(line)
```

### 지원 명령어

| 입력 | 동작 |
|------|------|
| `add <제목>` | TodoModel::add() 호출 |
| `done <id>` | TodoModel::complete() 호출 |
| `del <id>` | TodoModel::remove() 호출 |
| `quit` | 루프 종료 |
| 그 외 | "알 수 없는 명령어" 메시지 출력 |

### onModelChanged() 흐름

변경 이벤트를 받으면 `view_.renderList(model_.items())` 를 호출해 화면을 즉시 갱신한다.

---

## 6. main()

```cpp
int main() {
    TodoController controller;
    controller.run();
}
```

Controller 생성 후 run() 호출만 담당. 어떤 레이어 세부 사항도 포함하지 않는다.

---

## 7. 성공 기준

- 빌드 후 콘솔에서 직접 실행 시:
  - `add`, `done`, `del`, `quit` 명령어가 동작한다.
  - `std::cout` 호출이 View 레이어에만 존재한다.
  - `std::cin` 호출이 Controller 레이어에만 존재한다.
  - Model이 View/Controller 헤더를 `#include` 하지 않는다.
