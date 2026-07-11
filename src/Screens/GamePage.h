//
// Created by Magoumi on 7/11/2026.
//

#pragma once
#ifndef ALIENINVASION_GAME_PAGE_H
#define ALIENINVASION_GAME_PAGE_H
#include "Screen.h"

class GamePage : public Screen
{
    public:
    GamePage(); // Constructor
    ~GamePage() override; // Destructor

    ScreenAction Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_GAME_PAGE_H
