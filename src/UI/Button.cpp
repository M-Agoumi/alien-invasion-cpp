//
// Created by Magoumi on 7/10/2026.
//
#include "Button.h"

#include <utility>

Button::Button(float x, float y, float width, float height, std::string buttonText) {
    bounds = { x, y, width, height };
    text = std::move(buttonText);
    isHovered = false;

    // Default styling (Deep blue to match the space theme)
    normalColor = { 20, 30, 60, 255 };
    hoverColor = { 40, 60, 100, 255 };
    textColor = WHITE;
}

void Button::Update() {
    // 1. Get the current mouse coordinates
    Vector2 mousePos = GetMousePosition();

    // 2. Check if the mouse is inside our rectangle
    isHovered = CheckCollisionPointRec(mousePos, bounds);
}

void Button::Draw() {
    // 1. Pick the background color based on the hover state
    Color bgColor = isHovered ? hoverColor : normalColor;

    // 2. Draw the button body
    DrawRectangleRec(bounds, bgColor);

    // 3. Draw a nice border around it for a polished look
    DrawRectangleLinesEx(bounds, 2.0f, WHITE);

    // 4. Center the text inside the button
    // (We do a little math to find the middle of the rectangle)
    int fontSize = 20;
    int textWidth = MeasureText(text.c_str(), fontSize);

    float textX = bounds.x + (bounds.width / 2.0f) - (textWidth / 2.0f);
    float textY = bounds.y + (bounds.height / 2.0f) - (fontSize / 2.0f);

    DrawText(text.c_str(), (int)textX, (int)textY, fontSize, textColor);
}

void Button::SetText(std::string newText)
{
    this->text = std::move(newText);
}

bool Button::IsClicked() {
    // It's only a click if the mouse is hovering AND the left button was pressed THIS frame
    return isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}