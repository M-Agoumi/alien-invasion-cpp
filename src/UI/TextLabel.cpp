//
// Created by Magoumi on 7/10/2026.
//

#include "TextLabel.h"

#include <utility>

TextLabel::TextLabel(const std::string& text, const int fontSize, const Color color) {
    this->text = text;
    this->fontSize = fontSize;
    this->color = color;
}

void TextLabel::SetText(std::string newText) {
    this->text = std::move(newText);
}

void TextLabel::DrawCentered() {
    // 1. Measure the width of the string in pixels
    // (We use .c_str() because Raylib expects a C-style string, not a C++ std::string)
    int textWidth = MeasureText(text.c_str(), fontSize);

    // 2. Calculate the exact center coordinates
    int x = (GetScreenWidth() / 2) - (textWidth / 2);
    int y = (GetScreenHeight() / 2) - (fontSize / 2);

    // 3. Draw it
    DrawText(text.c_str(), x, y, fontSize, color);
}

void TextLabel::DrawAt(int x, int y) const
{
    DrawText(text.c_str(), x, y, fontSize, color);
}

void TextLabel::DrawCenteredX(int y) {
    // Measure width to find the horizontal center
    int textWidth = MeasureText(text.c_str(), fontSize);
    int x = (GetScreenWidth() / 2) - (textWidth / 2);

    // Draw using the calculated X, and the provided Y
    DrawText(text.c_str(), x, y, fontSize, color);
}

void TextLabel::DrawCenteredY(int x) {
    // Font size acts as the height, so we use it to find the vertical center
    int y = (GetScreenHeight() / 2) - (fontSize / 2);

    // Draw using the provided X, and the calculated Y
    DrawText(text.c_str(), x, y, fontSize, color);
}