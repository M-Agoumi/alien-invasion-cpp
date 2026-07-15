//
// Created by Magoumi on 7/11/2026.
//

#include "GamePage.h"

#include "../UI/TextLabel.h"

GamePage::GamePage()
{
    pageTitle = new TextLabel("Game Page", 40, WHITE);
    this->starTexture = LoadTexture("resources/images/star_01_16x16.bmp");
    this->spaceshipTexture = LoadTexture("resources/images/spaceship_icon.bmp");
    this->shipFireTexture = LoadTexture("resources/images/ship_fire_119x110.png");

    // Generate 150 stars right when the page loads
    GenerateStars();
}

GamePage::~GamePage()
{
    delete pageTitle;
    UnloadTexture(this->starTexture);
    UnloadTexture(this->spaceshipTexture);
    UnloadTexture(this->shipFireTexture);
}

void GamePage::GenerateStars() {
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

ScreenAction GamePage::Update()
{
    // Listen for the OS telling us the window bounds changed
    if (IsWindowResized()) {
        stars.clear();      // 1. Wipe out the old stars so we don't leak memory
        GenerateStars();    // 2. Run the grid math again for the new dimensions
    }

    // move stars
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

    // For now, we just return None to keep the page active
    return ScreenAction::None;
}

void GamePage::animateFire(int shipX, int shipY)
{
    // Sprite sheet layout: frames are 119x110, laid out 5 per row.
    // Rows 0..2 are full (5 frames each) and row 3 has only 3 frames,
    // for a total of 5 + 5 + 5 + 3 = 18 frames.
    const int frameWidth   = 119;
    const int frameHeight  = 110;
    const int framesPerRow  = 5;
    const int totalFrames   = 18;
    const float frameDuration = 0.02f; // 20 ms per frame

    // Advance the animation using frame-rate-independent timing
    fireTimer += GetFrameTime();
    while (fireTimer >= frameDuration) {
        fireTimer -= frameDuration;
        fireFrame = (fireFrame + 1) % totalFrames; // loop back to the start
    }

    // Locate the current frame inside the sprite sheet
    int col = fireFrame % framesPerRow;
    int row = fireFrame / framesPerRow;
    Rectangle source = {
        (float)(col * frameWidth),
        (float)(row * frameHeight),
        (float)frameWidth,
        (float)frameHeight
    };

    // Draw the flame scaled down, keeping its aspect ratio
    float fireW = 40.0f;
    float fireH = fireW * ((float)frameHeight / (float)frameWidth);

    // Rotate the flame 90 degrees. Rotation happens around the origin,
    // so we center the origin and treat dest's x/y as the center point.
    float rotation = 90.0f;
    Rectangle dest = {
        (float)shipX,                // center X (rotation pivot)
        (float)shipY + fireH / 2.0f, // center Y (rotation pivot)
        fireW,
        fireH
    };
    Vector2 origin = { fireW / 2.0f, fireH / 2.0f };

    DrawTexturePro(shipFireTexture, source, dest, origin, rotation, WHITE);
}

void GamePage::Draw()
{
    for (const auto& star : stars)
    {
        // DrawTextureEx takes: texture, position, rotation, scale, tint
        DrawTextureEx(starTexture, star.position, 0.0f, star.scale, star.tint);
    }
    // pageTitle->DrawCenteredX(100); // Draw the title at the top center of the screen

    // Draw the spaceship resized to a custom width/height using DrawTexturePro
    float shipW = 48.0f;   // desired width  (original texture is 64)
    float shipH = 77.0f;   // desired height
    Rectangle shipSource = { 0.0f, 0.0f, (float)spaceshipTexture.width, (float)spaceshipTexture.height };
    Rectangle shipDest   = {
        (float)GetScreenWidth() / 2.0f - shipW / 2.0f,   // centered horizontally
        (float)GetScreenHeight() - shipH - 30.0f,        // anchored near the bottom
        shipW,
        shipH
    };
    DrawTexturePro(spaceshipTexture, shipSource, shipDest, { 0.0f, 0.0f }, 0.0f, WHITE);

    // Draw the animated engine fire at the bottom-center of the ship
    int fireX = (int)(shipDest.x + shipW / 2.0f);
    int fireY = (int)(shipDest.y + shipH);
    animateFire(fireX, fireY);

    DrawFPS(GetScreenWidth() - 85, 10);
}
