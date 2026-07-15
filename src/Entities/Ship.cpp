//
// Created by Magoumi on 7/15/2026.
//

#include "Ship.h"

#include "raylib.h"

Ship::Ship()
{
    this->spaceshipTexture = LoadTexture("resources/images/spaceship_icon.bmp");
    this->shipFireTexture = LoadTexture("resources/images/ship_fire_119x110.png");

    // Start the ship centered horizontally, near the bottom of the screen
    shipPosition.x = (float)GetScreenWidth() / 2.0f - shipWidth / 2.0f;
    shipPosition.y = (float)GetScreenHeight() - shipHeight - 20.0f;
}

Ship::~Ship()
{
    UnloadTexture(spaceshipTexture);
    UnloadTexture(shipFireTexture);
}

void Ship::Update()
{
    // Get the time in seconds it took to render the last frame
    float deltaTime = GetFrameTime();

    // --- Ship movement (frame-rate independent) ---
    // Arrow keys or WASD. IsKeyDown is true for as long as the key is held.
    float moveStep = this->shipSpeed * deltaTime;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) shipPosition.x -= moveStep;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) shipPosition.x += moveStep;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) shipPosition.y -= moveStep;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) shipPosition.y += moveStep;

    // Keep the ship fully inside the screen bounds
    if (shipPosition.x < 0.0f) shipPosition.x = 0.0f;
    if (shipPosition.y < 0.0f) shipPosition.y = 0.0f;
    if (shipPosition.x > (float)GetScreenWidth() - shipWidth)
        shipPosition.x = (float)GetScreenWidth() - shipWidth;
    if (shipPosition.y > (float)GetScreenHeight() - shipHeight)
        shipPosition.y = (float)GetScreenHeight() - shipHeight;
}

void Ship::animateFire(int shipX, int shipY)
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

void Ship::Draw()
{
    // Draw the spaceship resized to a custom width/height using DrawTexturePro
    float shipW = shipWidth;
    float shipH = shipHeight;
    Rectangle shipSource = { 0.0f, 0.0f, (float)spaceshipTexture.width, (float)spaceshipTexture.height };
    Rectangle shipDest   = {
        shipPosition.x, // driven by keyboard input in Update()
        shipPosition.y,
        shipW,
        shipH
    };
    DrawTexturePro(spaceshipTexture, shipSource, shipDest, { 0.0f, 0.0f }, 0.0f, WHITE);

    // Draw the animated engine fire at the bottom-center of the ship
    int fireX = (int)(shipDest.x + shipW / 2.0f);
    int fireY = (int)(shipDest.y + shipH);
    animateFire(fireX, fireY);
}