//
// Created by Magoumi on 7/11/2026.
//

#include "GamePage.h"

GamePage::GamePage()
= default;

GamePage::~GamePage() = default;

ScreenAction GamePage::Update()
{
    this->space.Update(); // Update the background stars
    this->ship.Update(); // Update the ship

    // For now, we just return None to keep the page active
    return ScreenAction::None;
}

void GamePage::Draw()
{
    this->space.Draw(); // Draw the background stars
    this->ship.Draw(); // Draw the ship

    DrawFPS(GetScreenWidth() - 85, 10);
}
