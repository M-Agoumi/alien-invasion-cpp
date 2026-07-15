//
// Created by Magoumi on 7/11/2026.
//

#pragma once
#ifndef ALIENINVASION_GAME_PAGE_H
#define ALIENINVASION_GAME_PAGE_H

#include <vector>

#include "Screen.h"
#include "../Entities/Ship.h"
#include "../Entities/Space.h"
#include "../UI/TextLabel.h"

class GamePage : public Screen
{
    Space space; // Background starfield
    Ship ship; // The player's spaceship


public:
    GamePage(); // Constructor
    ~GamePage() override; // Destructor

    ScreenAction Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_GAME_PAGE_H
