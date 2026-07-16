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

# Dependencies are downloaded once. Don't run a git "update" step on every
# configure: it's faster, works offline, and (importantly) doesn't fail if the
# dependency .git folders have been removed to keep them out of the IDE's VCS log.
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# If a dependency's source has already been fetched into this build tree, reuse
# it directly. Setting FETCHCONTENT_SOURCE_DIR_<NAME> makes FetchContent skip
# ALL download/update/git steps for that dependency and just use the folder as
# is -- so the build no longer needs the nested .git repos to exist.
foreach(dep raylib raygui)
  set(_dep_src "${CMAKE_BINARY_DIR}/_deps/${dep}-src")
  if(EXISTS "${_dep_src}")
    string(TOUPPER ${dep} _DEP_UPPER)
    set(FETCHCONTENT_SOURCE_DIR_${_DEP_UPPER} "${_dep_src}")
  endif()
endforeach()
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5 # Pinned release tag (avoid `master`, which forces a
                    # rebase/fetch on every configure and can cause conflicts)
        GIT_SHALLOW TRUE
)
FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG 4.0 # Pinned release tag (see note above)
        GIT_SHALLOW TRUE
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
        src/Sounds/SoundManager.cpp
        src/Sounds/SoundManager.h
        src/Settings/GameSettings.h
        src/Entities/Bullet.cpp
        src/Entities/Bullet.h
)

# Link raylib to our game
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# raygui is header-only: just make its header available on the include path
target_include_directories(${PROJECT_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)

