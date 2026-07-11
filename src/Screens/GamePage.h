//
// Created by Magoumi on 7/11/2026.
//

#pragma once
#ifndef ALIENINVASION_GAME_PAGE_H
#define ALIENINVASION_GAME_PAGE_H

#include <vector>

#include "Screen.h"
#include "../UI/TextLabel.h"

struct BackgroundStar
{
    Vector2 position;
    float scale;
    Color tint; // Let us make some stars dimmer for depth!
};

class GamePage : public Screen
{
    TextLabel* pageTitle;
    Texture2D starTexture;

    // Our array (vector) of stars
    std::vector<BackgroundStar> stars;

    // Helper method to generate the field
    void GenerateStars();

public:
    GamePage(); // Constructor
    ~GamePage() override; // Destructor

    ScreenAction Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_GAME_PAGE_H
