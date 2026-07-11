//
// Created by Magoumi on 7/10/2026.
//

#pragma once
#ifndef ALIENINVASION_HOMEPAGE_H
#define ALIENINVASION_HOMEPAGE_H

#include "raylib.h"
#include "Screen.h"
#include "../UI/Button.h"

class HomePage : public Screen
{
    Texture2D background{};
    Rectangle sourceRec{};
    Rectangle destRec{};
    Button* btnStart;
    Button* btnSettings;
    Button* btnExit;

    // Helper method so we don't repeat the math
    void CalculateLayout();

public:
    HomePage(); // Constructor
    ~HomePage() override; // Destructor

    ScreenAction Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_HOMEPAGE_H
