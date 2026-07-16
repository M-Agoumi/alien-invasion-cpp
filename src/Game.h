//
// Created by Magoumi on 7/7/2026.
//

#ifndef ALIENINVASION_GAME_H
#define ALIENINVASION_GAME_H
#pragma once
#include "Screens/Screen.h"
#include "Sounds/SoundManager.h"

// Represents where the player currently is in the application
enum class GameState
{
    HomePage,   // On the home/main menu page
    InGame,     // Playing the game
    Settings    // On the settings page
};

class Game
{
private:
    int screenWidth;
    int screenHeight;
    bool isRunning;
    // This pointer will hold whatever page is currently active
    Screen* currentScreen;
    // Owns the game's audio (background music). Created after the audio
    // device is initialized in the constructor.
    SoundManager* soundManager;

public:
    Game (int width, int height); // constructor
    ~Game(); // destructure

    void Draw();
    void Update();
    void Run();
};

#endif //ALIENINVASION_GAME_H
