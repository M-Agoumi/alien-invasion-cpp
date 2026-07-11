//
// Created by Magoumi on 7/7/2026.
//

#include  "Game.h"
#include "raylib.h"
#include "Screens/HomePage.h"
#include "Screens/SettingPage.h"

Game::Game(const int width, const int height)
{
    this->screenWidth = width;
    this->screenHeight = height;
    this->isRunning = true;

    // 1. Initialize the system
    InitWindow(screenWidth, screenHeight, "Alien Invasion");
    SetTargetFPS(120);

    this->currentScreen = new HomePage();
}

Game::~Game()
{
    // Close the system
    delete this->currentScreen;
    CloseWindow();
}

void Game::Update()
{
    // Pass the update logic down to the active screen
    if (this->currentScreen != nullptr) {
        // Grab the action from the current screen
        ScreenAction action = this->currentScreen->Update();

        // Handle the routing based on the action
        if (action == ScreenAction::Exit) {
            this->isRunning = false; // This will break the main loop!
        }
        if (action == ScreenAction::GoToSettings) {
            delete this->currentScreen; // Clean up the old screen
            this->currentScreen = new SettingPage(); // Switch to Settings
        }
        if (action == ScreenAction::GoToHome) {
            delete this->currentScreen; // Clean up the old screen
            this->currentScreen = new HomePage(); // Switch to Home
        }
        // We will add the logic to switch to InGame and Settings here next!
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(CLITERAL(Color){ 20, 20, 20, 255 });

    // Look at how clean this is! Polymorphism in action.
    // It will automatically call HomePage::Draw() because that's what's loaded.
    if (this->currentScreen != nullptr) {
        this->currentScreen->Draw();
    }

    EndDrawing();
}

void Game::Run() {
    // Main game loop
    while (this->isRunning && !WindowShouldClose()) {
        // 1. INPUT & UPDATE (We will add ship movement here soon)
        this->Update();
        // 2. DRAW
        this->Draw();
    }
}
