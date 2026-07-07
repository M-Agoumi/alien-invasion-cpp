cmake_minimum_required(VERSION 3.25)
project(alien_invasion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake 4.x removed compatibility with projects that request
# cmake_minimum_required(VERSION < 3.5). raylib 5.0 / json still do,
# so allow them to configure by pinning a minimum policy version.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Enable FetchContent
include(FetchContent)

# Fetch Raylib (using SYSTEM to suppress warnings from its headers)
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
  SYSTEM
)
# Set Raylib options before making it available
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(SUPPORT_GIF_RECORDING OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_BMP ON CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Fetch nlohmann/json (using SYSTEM to suppress warnings from its headers)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
  SYSTEM
)
FetchContent_MakeAvailable(json)

# Suppress compiler warnings when compiling third-party libraries (raylib/glfw)
if(TARGET raylib)
  target_compile_options(raylib PRIVATE -w)
endif()
if(TARGET glfw)
  target_compile_options(glfw PRIVATE -w)
endif()

# Add our executable (only compiling main.cpp for start fresh)
add_executable(alien_invasion
  src/main.cpp
        src/game.cpp
        src/game.h
)

# Enable high warning level for our own code
if(MSVC)
  target_compile_options(alien_invasion PRIVATE /W4)
else()
  target_compile_options(alien_invasion PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link dependencies
target_link_libraries(alien_invasion PRIVATE raylib nlohmann_json::nlohmann_json)

# Include directories
target_include_directories(alien_invasion PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
