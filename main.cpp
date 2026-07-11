#include "raylib.h"
#include "src/Game.h"

int main() {
    // Initialization
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 800;

    Game game(screenWidth, screenHeight);
    game.Run();

    return 0;
}
