//
// Created by Magoumi on 7/15/2026.
//

#include "Ship.h"

#include "raylib.h"

Ship::Ship()
{
    this->spaceshipTexture = LoadTexture("resources/images/ship/spaceship_icon.bmp");
    this->spaceshipRightTexture = LoadTexture("resources/images/ship/spaceship_right.bmp");
    this->spaceshipLeftTexture = LoadTexture("resources/images/ship/spaceship_left_1.bmp");
    this->shipFireTexture = LoadTexture("resources/images/ship/ship_fire_119x110.png");

    // Start the ship centered horizontally, near the bottom of the screen
    shipPosition.x = static_cast<float>(GetScreenWidth()) / 2.0f - shipWidth / 2.0f;
    shipPosition.y = static_cast<float>(GetScreenHeight()) - shipHeight - 20.0f;
}

Ship::~Ship()
{
    UnloadTexture(spaceshipTexture);
    UnloadTexture(spaceshipRightTexture);
    UnloadTexture(spaceshipLeftTexture);
    UnloadTexture(shipFireTexture);
}

void Ship::Update()
{
    // Get the time in seconds it took to render the last frame
    const float deltaTime = GetFrameTime();

    // --- Ship movement (frame-rate independent) ---
    // Arrow keys or WASD. IsKeyDown is true for as long as the key is held.
    const float moveStep = this->shipSpeed * deltaTime;
    isMovingLeft = false;
    isMovingRight = false;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)){shipPosition.x -= moveStep; isMovingLeft = true; isMovingRight = false;}
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){shipPosition.x += moveStep; isMovingRight = true; isMovingLeft = false;}
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) shipPosition.y -= moveStep;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) shipPosition.y += moveStep;

    // Keep the ship fully inside the screen bounds
    if (shipPosition.x < 0.0f) shipPosition.x = 0.0f;
    if (shipPosition.y < 0.0f) shipPosition.y = 0.0f;
    if (shipPosition.x > static_cast<float>(GetScreenWidth()) - shipWidth)
        shipPosition.x = static_cast<float>(GetScreenWidth()) - shipWidth;
    if (shipPosition.y > static_cast<float>(GetScreenHeight()) - shipHeight)
        shipPosition.y = static_cast<float>(GetScreenHeight()) - shipHeight;

    // limit the ship to 70% of the screen height
    const float minY = static_cast<float>(GetScreenHeight()) * 0.3f - shipHeight;
    if (shipPosition.y < minY) shipPosition.y = minY;
}

void Ship::animateFire(int shipX, int shipY)
{
    // Sprite sheet layout: frames are 119x110, laid out 5 per row.
    // Rows 0..2 are full (5 frames each) and row 3 has only 3 frames,
    // for a total of 5 + 5 + 5 + 3 = 18 frames.
    constexpr int frameWidth   = 119;
    constexpr int frameHeight  = 110;
    constexpr int framesPerRow  = 5;
    constexpr int totalFrames   = 18;
    constexpr float frameDuration = 0.02f; // 20 ms per frame

    // Advance the animation using frame-rate-independent timing
    fireTimer += GetFrameTime();
    // NOLINT(bugprone-infinite-loop) -- this loop is guaranteed to terminate because fireTimer decreases each iteration
    while (fireTimer >= frameDuration) {
        fireTimer -= frameDuration;
        fireFrame = (fireFrame + 1) % totalFrames; // loop back to the start
    }

    // Locate the current frame inside the sprite sheet
    const int col = fireFrame % framesPerRow;
    const int row = fireFrame / framesPerRow;
    const Rectangle source = {
        static_cast<float>(col * frameWidth),
        static_cast<float>(row * frameHeight),
        static_cast<float>(frameWidth),
        static_cast<float>(frameHeight)
    };

    // Draw the flame scaled down, keeping its aspect ratio
    constexpr float fireW = 40.0f;
    constexpr float fireH = fireW * (static_cast<float>(frameHeight) / static_cast<float>(frameWidth));

    // Rotate the flame 90 degrees. Rotation happens around the origin,
    // so we center the origin and treat destination's x/y as the center point.
    constexpr float rotation = 90.0f;
    Rectangle dest = {
        static_cast<float>(shipX),                // center X (rotation pivot)
        static_cast<float>(shipY) + fireH / 2.0f, // center Y (rotation pivot)
        fireW,
        fireH
    };
    constexpr Vector2 origin = { fireW / 2.0f, fireH / 2.0f };

    DrawTexturePro(shipFireTexture, source, dest, origin, rotation, WHITE);
}

void Ship::Draw()
{
    // Draw the spaceship resized to a custom width/height using DrawTexturePro
    const float shipW = shipWidth;
    const float shipH = shipHeight;
    const Rectangle shipSource = { 0.0f, 0.0f, static_cast<float>(spaceshipTexture.width), static_cast<float>(spaceshipTexture.height) };
    const Rectangle shipDest   = {
        shipPosition.x, // driven by keyboard input in Update()
        shipPosition.y,
        shipW,
        shipH
    };
    if (isMovingRight) {
        DrawTexturePro(spaceshipRightTexture, shipSource, shipDest, { 0.0f, 0.0f }, 0.0f, WHITE);
    } else if (isMovingLeft) {
        DrawTexturePro(spaceshipLeftTexture, shipSource, shipDest, { 0.0f, 0.0f }, 0.0f, WHITE);
    } else {
        DrawTexturePro(spaceshipTexture, shipSource, shipDest, { 0.0f, 0.0f }, 0.0f, WHITE);
    }

    // Draw the animated engine fire at the bottom-center of the ship
    const int fireX = static_cast<int>(shipDest.x + shipW / 2.0f);
    const int fireY = static_cast<int>(shipDest.y + shipH);
    animateFire(fireX, fireY);
}