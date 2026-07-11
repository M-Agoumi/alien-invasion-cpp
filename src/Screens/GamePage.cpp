//
// Created by Magoumi on 7/11/2026.
//

#include "GamePage.h"

#include "../UI/TextLabel.h"

GamePage::GamePage()
{
    pageTitle = new TextLabel("Game Page", 40, WHITE);
    this->starTexture = LoadTexture("resources/images/star_01_16x16.bmp");

    // Generate 150 stars right when the page loads
    GenerateStars();
}

GamePage::~GamePage()
{
    delete pageTitle;
    UnloadTexture(this->starTexture);
}

void GamePage::GenerateStars() {
    // 1. Define our invisible grid
    int cellSize = 80; // An 80x80 pixel box for each star
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

ScreenAction GamePage::Update()
{
    // Listen for the OS telling us the window bounds changed
    if (IsWindowResized()) {
        stars.clear();      // 1. Wipe out the old stars so we don't leak memory
        GenerateStars();    // 2. Run the grid math again for the new dimensions
    }
    // For now, we just return None to keep the page active
    return ScreenAction::None;
}

void GamePage::Draw()
{
    for (const auto& star : stars)
    {
        // DrawTextureEx takes: texture, position, rotation, scale, tint
        DrawTextureEx(starTexture, star.position, 0.0f, star.scale, star.tint);
    }
    // pageTitle->DrawCenteredX(100); // Draw the title at the top center of the screen
}
