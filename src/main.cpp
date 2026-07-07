// #include <raylib.h>
#include <iostream>

// int main() {
//     // 1. Initialize Window
//     const int screen_width = 1200;
//     const int screen_height = 800;
//     InitWindow(screen_width, screen_height, "Alien Invasion C++");
//     SetTargetFPS(60);
//
//     // Set application window icon if it exists
//     Image icon = LoadImage("icon.jpeg");
//     if (icon.data != nullptr) {
//         SetWindowIcon(icon);
//         UnloadImage(icon);
//     }
//
//     // 2. Main Game Loop
//     while (!WindowShouldClose()) {
//         // Update states here...
//
//         // Draw frames
//         BeginDrawing();
//         ClearBackground(Color{20, 20, 20, 255});
//
//         // Simple centered boilerplate text
//         const char* msg1 = "Alien Invasion C++ Blank Slate";
//         const char* msg2 = "Start Coding Your Game Here!";
//         const char* msg3 = "Press ESC to Exit";
//
//         DrawText(msg1, (screen_width - MeasureText(msg1, 30)) / 2, 300, 30, RAYWHITE);
//         DrawText(msg2, (screen_width - MeasureText(msg2, 20)) / 2, 360, 20, LIGHTGRAY);
//         DrawText(msg3, (screen_width - MeasureText(msg3, 20)) / 2, 420, 20, GRAY);
//
//         EndDrawing();
//     }
//
//     // 3. Close Window & Deinitialize
//     CloseWindow();
//     return 0;
// }

int main()
{
    // print hello world
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
