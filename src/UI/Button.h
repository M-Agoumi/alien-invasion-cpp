//
// Created by Magoumi on 7/10/2026.
//
#pragma once
#ifndef ALIENINVASION_BUTTON_H
#define ALIENINVASION_BUTTON_H

#include "raylib.h"
#include <string>

class Button
{
private:
    Rectangle bounds{};
    std::string text;
    bool isHovered;

    // Visuals (You can tweak these colors later!)
    Color normalColor{};
    Color hoverColor{};
    Color textColor{};

public:
    // Constructor: Needs position, size, and the text
    Button(float x, float y, float width, float height, std::string buttonText);

    // Core methods
    void Update();
    void Draw();
    void SetText(std::string newText);

    // This is how our HomePage will know when to change screens
    bool IsClicked();
};
#endif //ALIENINVASION_BUTTON_H
