//
// Created by Magoumi on 7/10/2026.
//

#include "SettingPage.h"

#include "raylib.h"
#include "raygui.h"

SettingPage::SettingPage() {
    // Load any resources needed for the settings page here
    titleLabel = new TextLabel("Settings", 40, WHITE);
    btnBack = new Button(75, 500, 200, 50, "BACK");
    btnFullscreen = new Button(75, 200, 200, 50, "FULLSCREEN: Off");
    btnMute = new Button(75, 300, 200, 50, "MUTE");
    isFullscreen = false;
    volumeLevel = 25.0f; // Default volume level
}

SettingPage::~SettingPage()
{
    delete titleLabel;
    delete btnBack;
    delete btnFullscreen;
    delete btnMute;
}

ScreenAction SettingPage::Update() {
    // Handle input and update logic for the settings page here
    // For now, we'll just return None to keep the page active
    btnBack->Update();
    btnFullscreen->Update();
    btnMute->Update();

    // check for clicks
    if (btnBack->IsClicked()) {
        return ScreenAction::GoToHome;
    }
    if (btnFullscreen->IsClicked()) {
        // btnFullscreen->set
        isFullscreen = !isFullscreen;
        btnFullscreen->SetText(isFullscreen ? "Fullscreen: On" : "Fullscreen: Off");

        ToggleFullscreen(); // This is the Raylib function that actually toggles fullscreen
        int monitor = GetCurrentMonitor();

        if (IsWindowFullscreen()) {
            SetWindowState(FLAG_WINDOW_UNDECORATED); // Strip the title bar explicitly
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            SetWindowPosition(0, 0); // Lock it to the top left corner
        } else {
            // 2. Going back to Windowed
            ClearWindowState(FLAG_WINDOW_UNDECORATED); // Bring the title bar back

            // Replace these with your actual game window dimensions!
            int windowWidth = 1000;
            int windowHeight = 800;

            SetWindowSize(windowWidth, windowHeight);

            // Force it to center so the title bar isn't stuck under your top taskbar
            SetWindowPosition(
                (GetMonitorWidth(monitor) / 2) - (windowWidth / 2),
                (GetMonitorHeight(monitor) / 2) - (windowHeight / 2)
            );
        }
    }
    if (btnMute->IsClicked()) {
        // Implement mute functionality here
    }

    return ScreenAction::None;
}

void SettingPage::Draw() {
    // DrawText("Alien Invasion - HOME", 200, 200, 40, CLITERAL(Color){ 255, 255, 255, 255 });
    // 1. Define your gradient colors
    Color topColor = { 1, 1, 10, 255 };
    Color bottomColor = { 2, 3, 22, 255 };

    // 2. Draw the vertical gradient across the entire screen
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), topColor, bottomColor);

    // DrawText("Settings Page", 200, 100, 40, CLITERAL(Color){ 255, 255, 255, 255 });
    titleLabel->DrawCenteredX(100);
    btnBack->Draw();
    btnFullscreen->Draw();
    // btnMute->Draw();

    GuiSlider((Rectangle){ 75, 300, 240, 24 }, "VOLUME: ",
              TextFormat("%.0f", volumeLevel), &volumeLevel, 0.0f, 100.0f);
}
