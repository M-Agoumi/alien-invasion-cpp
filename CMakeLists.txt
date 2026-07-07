cmake_minimum_required(VERSION 3.16)
project(alien_invasion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable FetchContent
include(FetchContent)

# Fetch Raylib
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
# Set Raylib options before making it available
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(SUPPORT_GIF_RECORDING OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_BMP ON CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Fetch nlohmann/json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Add our executable
add_executable(alien_invasion
  src/main.cpp
  src/game.cpp
  src/setting.cpp
  src/parser.cpp
  src/sound_manager.cpp
  src/drawer.cpp
  src/bullet.cpp
  src/ship.cpp
  src/alien.cpp
  src/explosion.cpp
  src/level.cpp
)

# Link dependencies
target_link_libraries(alien_invasion PRIVATE raylib nlohmann_json::nlohmann_json)

# Include directories
target_include_directories(alien_invasion PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
