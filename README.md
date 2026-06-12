# ConsoleMVC-KHNam-CRA-3

C++20 콘솔 애플리케이션 MVC 아키텍처 PoC.  
Model / View / Controller 레이어 역할 분리를 Todo 도메인으로 시연한다.

## 아키텍처

```
main()
  └─ TodoController::run()
        ├─ std::cin  ──────────────────► handleInput()
        ├─ TodoModel (상태 + 이벤트)
        │     └─ onChanged_(TodoEvent, id) ──► onModelChanged()
        └─ TodoView  (std::cout 전담)
```

| 레이어 | 위치 | 책임 |
|--------|------|------|
| Model | `Model/` | 데이터 구조 · 비즈니스 로직 · 이벤트 발행 |
| View | `View/` | 콘솔 출력 전담 (`std::cout` 허용) |
| Controller | `Controller/` | 입력 수신(`std::cin`) · Model 갱신 · View 호출 조율 |

## 빌드

Visual Studio 2022, MSVC v145, C++20

```powershell
# Debug x64
msbuild ConsoleMVC-KHNam-CRA-3.slnx /p:Configuration=Debug /p:Platform=x64

# Release x64
msbuild ConsoleMVC-KHNam-CRA-3.slnx /p:Configuration=Release /p:Platform=x64
```

빌드 결과물: `x64\Debug\` 또는 `x64\Release\`

## 실행

```
x64\Debug\ConsoleMVC-KHNam-CRA-3.exe
```

## 명령어

| 입력 | 동작 |
|------|------|
| `add <제목>` | 할 일 추가 |
| `done <id>` | 완료 처리 |
| `del <id>` | 삭제 |
| `quit` | 종료 |

## 실행 예시

```
--- Todo 목록 (0건) ---
  (비어 있음)
-------------------------
명령어: add <제목> | done <id> | del <id> | quit
> add 장보기

--- Todo 목록 (1건) ---
  [ ] 1. 장보기
-------------------------
> done 1

--- Todo 목록 (1건) ---
  [x] 1. 장보기
-------------------------
> quit
```
