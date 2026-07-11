//
// Created by Magoumi on 7/10/2026.
//

#pragma once
#ifndef ALIENINVASION_TEXT_LABEL_H
#define ALIENINVASION_TEXT_LABEL_H

#include "raylib.h"
#include <string>

class TextLabel
{
private:
    std::string text;
    int fontSize;
    Color color{};

public:
    TextLabel(const std::string& text, int fontSize, Color color);

    // Allowing us to update the text dynamically later (e.g., Score: 100)
    void SetText(std::string newText);

    // Drawing methods
    void DrawCentered(); // Calculates the exact middle of the screen
    void DrawAt(int x, int y) const; // Draws at a specific coordinate
    void DrawCenteredX(int y); // Centers horizontally, uses your Y
    void DrawCenteredY(int x); // Centers vertically, uses your X
};
#endif //ALIENINVASION_TEXT_LABEL_H
