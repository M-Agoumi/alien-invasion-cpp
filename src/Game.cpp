//
// Created by Magoumi on 7/7/2026.
//

#include  "Game.h"

#include <iostream>
#include <ostream>

#include "raylib.h"
#include "Screens/GamePage.h"
#include "Screens/HomePage.h"
#include "Screens/SettingPage.h"
#include "Settings/GameSettings.h"

Game::Game(const int width, const int height)
{
    this->screenWidth = width;
    this->screenHeight = height;
    this->isRunning = true;

    // 1. Initialize the system
    InitWindow(screenWidth, screenHeight, "Alien Invasion");

    // 1b. Initialize the audio device, then start the background music.
    // (The audio device MUST exist before any music/sound is loaded.)
    InitAudioDevice();
    this->soundManager = new SoundManager(); // starts looping music immediately

    // 2. Ask the OS exactly what the monitor's hardware refresh rate is
    int monitor = GetCurrentMonitor();
    int refreshRate = GetMonitorRefreshRate(monitor);

    std::cout << "refresh rate: " << refreshRate << std::endl;
    // Optional: Just in case the OS returns 0 (which happens on some setups), default to 120
    if (refreshRate == 0) {
        refreshRate = 120;
    }

    // 3. Force the engine to match the target FPS from settings.
    // targetFps == 0 means "match the monitor's refresh rate".
    GameSettings& settings = GameSettings::Get();
    int targetFps = settings.targetFps > 0 ? settings.targetFps : refreshRate;
    SetTargetFPS(targetFps);

    this->currentScreen = new HomePage(); // default page
    // this->currentScreen = new GamePage(); // while working in the page to save time on clicks
}

Game::~Game()
{
    // Close the system
    delete this->currentScreen;
    // Free the music stream before shutting the audio device down.
    delete this->soundManager;
    CloseAudioDevice();
    CloseWindow();
}

void Game::Update()
{
    // Keep the background music stream fed every frame.
    if (this->soundManager != nullptr) {
        this->soundManager->Update();
    }

    // Pass the update logic down to the active screen
    if (this->currentScreen != nullptr) {
        // Grab the action from the current screen
        ScreenAction action = this->currentScreen->Update();

        // Handle the game
        if (action == ScreenAction::GoToInGame) {
            delete this->currentScreen; // Clean up the old screen
            this->currentScreen = new GamePage(); // Switch to InGame
        }

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
