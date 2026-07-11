# Alien Invasion

A small 2D game written in C++17 using [raylib](https://github.com/raysan5/raylib)
for rendering/input and [raygui](https://github.com/raysan5/raygui) for the UI.

## Requirements

- **CMake** 3.14 or newer
- A **C++17** compiler (GCC, Clang, or MSVC)
- **Git** (used by CMake's `FetchContent` to download raylib and raygui)
- An internet connection for the first build (dependencies are fetched automatically)

raylib may require a few system development packages on Linux. On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential git cmake \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev \
    libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

## Building for the first time

From the project root:

```bash
# 1. Configure (downloads raylib + raygui, this step needs internet)
cmake -S . -B build

# 2. Build
cmake --build build
```

The first configure step clones raylib and raygui into `build/_deps/`, so it can
take a few minutes. Subsequent builds are much faster.

## Running

After a successful build the executable is placed in the `build/` directory:

```bash
./build/AlienInvasion
```

> Run the game from the project root so it can find the assets in `resources/`.

## Project structure

```
alien-invasion-cpp/
├── CMakeLists.txt        # Build configuration
├── main.cpp              # Entry point
├── resources/            # Game assets (images, etc.)
└── src/
    ├── Game.{h,cpp}      # Core game loop / state
    ├── raygui_impl.cpp   # raygui implementation unit
    ├── Screens/          # Home, Settings and Game screens
    └── UI/               # Reusable UI widgets (Button, TextLabel)
```

## Notes

- The build directories (`build/`, `cmake-build-*/`) are generated and are
  ignored by Git — they can be safely deleted and regenerated at any time.
- Dependencies track the `master` branch of raylib/raygui. To pin a specific
  release, change the `GIT_TAG` values in `CMakeLists.txt`.

