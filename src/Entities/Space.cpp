//
// Created by Magoumi on 7/15/2026.
//

#include "Space.h"

Space::Space()
{
    this->starTexture = LoadTexture("resources/images/space/star_01_16x16.bmp");

    // Generate stars right when the page loads
    GenerateStars();
}

Space::~Space()
{
    UnloadTexture(this->starTexture);
}

void Space::GenerateStars() {
    // 1. Define our invisible grid
    int cellSize = 60; // An 60x60 pixel box for each star
    int cols = GetScreenWidth() / cellSize;
    int rows = GetScreenHeight() / cellSize;

    Color starColors[] = {
        WHITE,
        { 173, 216, 230, 255 }, // Light Blue
        { 255, 255, 224, 255 }, // Light Yellow
        { 255, 182, 193, 255 }  // Light Pink
    };

    // 2. Loop through every row and column of our grid
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {

            // Optional: Give each cell a 20% chance to be empty
            // so it doesn't look TOO perfectly uniform
            if (GetRandomValue(1, 100) > 80) continue;

            BackgroundStar newStar;

            // 3. Find the exact boundaries of the current cell
            int cellStartX = col * cellSize;
            int cellStartY = row * cellSize;

            // 4. Pick a random position strictly INSIDE this specific cell
            newStar.position.x = (float)GetRandomValue(cellStartX, cellStartX + cellSize);
            newStar.position.y = (float)GetRandomValue(cellStartY, cellStartY + cellSize);

            // Scale (assuming you are using the 16x16 image now)
            newStar.scale = (float)GetRandomValue(50, 120) / 100.0f;

            // Color and Brightness
            Color baseColor = starColors[GetRandomValue(0, 3)];
            baseColor.a = (unsigned char)GetRandomValue(100, 255);
            newStar.tint = baseColor;

            stars.push_back(newStar);
        }
    }
}

void Space::Update()
{
    // Listen for the OS telling us the window bounds changed
    if (IsWindowResized()) {
        stars.clear();      // 1. Wipe out the old stars so we don't leak memory
        GenerateStars();    // 2. Run the grid math again for the new dimensions
    }

    // Get the time in seconds it took to render the last frame
    float deltaTime = GetFrameTime();

    // move stars
    for (auto& star : stars) {
        // 1. Parallax Effect: Base speed * star scale
        // A scale of 0.5 moves at 50px/sec, a scale of 1.2 moves at 120px/sec
        float speed = 100.0f * star.scale;

        // Move the star downwards (Frame-rate independent!)
        star.position.y += speed * deltaTime;

        // 2. Reset the star if it falls off the screen
        if (star.position.y > GetScreenHeight()) {
            star.position.y = -20; // Start slightly above the top edge
        }
    }


}

void Space::Draw()
{
    for (const auto& star : stars)
    {
        // DrawTextureEx takes: texture, position, rotation, scale, tint
        DrawTextureEx(this->starTexture, star.position, 0.0f, star.scale, star.tint);
    }
}
