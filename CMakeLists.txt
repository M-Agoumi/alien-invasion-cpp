cmake_minimum_required(VERSION 3.14)
project(AlienInvasion CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to a Release build when no build type is specified (e.g. a plain
# `cmake -S . -B build`). Silences raylib's "Default build type is not set".
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Fetch raylib directly
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master # Or specify a release tag like 4.5.0
)
FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG master # Or specify a release tag like 4.5.0
        # raygui is header-only. Point SOURCE_SUBDIR at a folder with no
        # CMakeLists.txt so MakeAvailable only downloads it (skips building
        # raygui's examples, which would otherwise need raylib via find_package).
        SOURCE_SUBDIR  do_not_build
)
FetchContent_MakeAvailable(raylib raygui)

# Our game executable
add_executable(${PROJECT_NAME} main.cpp
        src/Game.h
        src/Game.cpp
        src/raygui_impl.cpp
        src/Screens/Screen.h
        src/Screens/HomePage.cpp
        src/Screens/HomePage.h
        src/UI/Button.h
        src/UI/Button.cpp
        src/Screens/SettingPage.h
        src/Screens/SettingPage.cpp
        src/UI/TextLabel.cpp
        src/UI/TextLabel.h
        src/raygui_impl.cpp
        src/Screens/GamePage.cpp
        src/Screens/GamePage.h
        src/Entities/Ship.cpp
        src/Entities/Ship.h
        src/Entities/Space.cpp
        src/Entities/Space.h
        src/Entities/Entity.h
)

# Link raylib to our game
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# raygui is header-only: just make its header available on the include path
target_include_directories(${PROJECT_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)

