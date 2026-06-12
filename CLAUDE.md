## Project Overview

C++20 콘솔 애플리케이션. Model / Controller / View 패키지 구조와 역할 분리 PoC. Visual Studio 환경, MSBuild 빌드, 사용자가 직접 콘솔 실행으로 테스트.

## Build Commands

```powershell
# Debug x64 빌드 (기본)
msbuild ConsoleMVC-KHNam-CRA-3.slnx /p:Configuration=Debug /p:Platform=x64

# Release x64 빌드
msbuild ConsoleMVC-KHNam-CRA-3.slnx /p:Configuration=Release /p:Platform=x64

# 클린 후 빌드
msbuild ConsoleMVC-KHNam-CRA-3.slnx /t:Clean,Build /p:Configuration=Debug /p:Platform=x64
```

빌드 결과물 위치: `x64\Debug\` 또는 `x64\Release\`

## MVC Architecture

이 프로젝트는 다음 세 레이어로 역할을 분리한다:

- **Model** (`Model/`) ? 데이터 구조와 비즈니스 로직. View/Controller를 알지 못한다. 상태 변경 시 Observer 패턴이나 콜백으로 Controller에 알린다.
- **View** (`View/`) ? 콘솔 출력 전담. `std::cout` 호출은 View에만 위치한다. Model을 직접 참조하지 않고 Controller가 넘겨준 데이터만 렌더링한다.
- **Controller** (`Controller/`) ? 사용자 입력(`std::cin`) 수신, Model 갱신, View 호출을 조율한다. 레이어 간 유일한 중재자.

`main()` 은 Controller를 생성하고 실행 루프를 시작하는 역할만 담당한다.

## Key Constraints

- **C++20** (`stdcpp20`), MSVC toolset v145
- `std::cout` / `std::cin` 은 각각 View / Controller 레이어에만 허용
- 테스트는 빌드 후 직접 콘솔 실행으로 수행 (별도 테스트 프레임워크 없음)
- 새 소스 파일 추가 시 `.vcxproj` 의 `<ItemGroup>` 에 `<ClCompile>` 항목도 함께 추가해야 빌드에 포함됨
