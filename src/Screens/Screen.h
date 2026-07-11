//
// Created by Magoumi on 7/10/2026.
//

#pragma once
#ifndef ALIENINVASION_SCREEN_H
#define ALIENINVASION_SCREEN_H

// The different commands a screen can send back to the Game manager
enum class ScreenAction {
    None,           // Do nothing, just keep running
    GoToHome,       // Switch to HomePage
    GoToInGame,     // Switch to InGamePage
    GoToSettings,   // Switch to SettingPage
    Exit            // Kill the game
};

class Screen {
public:
    // A virtual destructor is required in C++ so child classes are cleaned up properly
    virtual ~Screen() = default;

    // The '= 0' makes these "pure virtual" methods.
    // It means this class cannot be instantiated directly, and any child
    // class MUST implement these methods. (Exactly like a PHP interface).
    virtual ScreenAction Update() = 0;
    virtual void Draw() = 0;
};

#endif //ALIENINVASION_SCREEN_H
