//
// Created by Magoumi on 7/10/2026.
//

#include "HomePage.h"

#include <iostream>
#include <ostream>

#include "raylib.h"


HomePage::HomePage() {
    // 1. LOAD: Pull the image from your hard drive into the GPU
    // Make sure the image name exactly matches your file.
    this->background = LoadTexture("resources/background.png");

    CalculateLayout();

    // Instantiate the buttons (X=100, Y=200, 300, 400)
    btnStart = new Button(75, 200, 200, 50, "START GAME");
    btnSettings = new Button(75, 300, 200, 50, "SETTINGS");
    btnExit = new Button(75, 400, 200, 50, "EXIT");
}

HomePage::~HomePage() {
    // 3. UNLOAD: Free up the GPU memory to prevent memory leaks
    UnloadTexture(this->background);
    delete btnStart;
    delete btnSettings;
    delete btnExit;
}

void HomePage::CalculateLayout() {
    // 1. Source rectangle
    float sourceWidth = (float)background.width;
    float sourceHeight = (float)background.height - 40.0f;
    sourceRec = { 0.0f, 40.0f, sourceWidth, sourceHeight };

    // 2. Scale and Destination rectangle
    float screenHeight = (float)GetScreenHeight();
    float screenWidth = (float)GetScreenWidth();

    float scale = screenHeight / sourceHeight;
    float destWidth = sourceWidth * scale;

    float destX = screenWidth - destWidth;

    destRec = { destX, 0.0f, destWidth, screenHeight };
}

ScreenAction HomePage::Update() {
    // ONLY recalculate if the user dynamically resizes the window
    if (IsWindowResized()) {
        CalculateLayout();
    }

    btnStart->Update();
    btnSettings->Update();
    btnExit->Update();

    // Check for clicks!
    if (btnStart->IsClicked()) {
        // We will trigger the InGamePage transition here soon
        return ScreenAction::GoToInGame;
    }
    if (btnSettings->IsClicked()) {
        return ScreenAction::GoToSettings;
    }
    if (btnExit->IsClicked()) {
        return ScreenAction::Exit;
    }

    return ScreenAction::None;
}

void HomePage::Draw() {
    // DrawText("Alien Invasion - HOME", 200, 200, 40, CLITERAL(Color){ 255, 255, 255, 255 });
    // 1. Define your gradient colors
    Color topColor = { 1, 1, 10, 255 };
    Color bottomColor = { 2, 3, 22, 255 };

    // 2. Draw the vertical gradient across the entire screen
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), topColor, bottomColor);

    // 3. Draw your optimized background image on top (anchored to the right)
    DrawTexturePro(background, sourceRec, destRec, { 0.0f, 0.0f }, 0.0f, WHITE);

    // 4. Draw buttons
    btnStart->Draw();
    btnSettings->Draw();
    btnExit->Draw();
}