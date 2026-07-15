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
    Texture2D spaceshipTexture;
    Texture2D shipFireTexture;

    // Fire animation state
    int fireFrame = 0;        // Current frame index (0..17)
    float fireTimer = 0.0f;   // Accumulated time toward the next frame

    // Our array (vector) of stars
    std::vector<BackgroundStar> stars;

    // Helper method to generate the field
    void GenerateStars();
    void animateFire(int shipX, int shipY);

public:
    GamePage(); // Constructor
    ~GamePage() override; // Destructor

    ScreenAction Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_GAME_PAGE_H
