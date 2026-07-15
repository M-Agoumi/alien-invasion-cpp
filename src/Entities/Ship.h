//
// Created by Magoumi on 7/15/2026.
//

#pragma once
#ifndef ALIENINVASION_SHIP_H
#define ALIENINVASION_SHIP_H
#include "Entity.h"
#include "raylib.h"

class Ship: public Entity
{
    Texture2D spaceshipTexture{};
    Texture2D spaceshipRightTexture{};
    Texture2D spaceshipLeftTexture{};
    Texture2D shipFireTexture{};
    bool isMovingRight = false;
    bool isMovingLeft = false;

    // Ship movement state
    Vector2 shipPosition = {0.0f, 0.0f}; // Top-left corner of the ship
    float shipSpeed = 300.0f; // Pixels per second
    float shipWidth = 48.0f;
    float shipHeight = 77.0f;

    // Fire animation state
    int fireFrame = 0; // Current frame index (0..17)
    float fireTimer = 0.0f; // Accumulated time toward the next frame

    void animateFire(int shipX, int shipY);
public:
    Ship();
    ~Ship() override;

    // Ship owns GPU textures, so copying it would double-free / dangle the
    // texture ids (the source of the "black boxes" bug). Forbid copying;
    // allow moving instead.
    Ship(const Ship&) = delete;
    Ship& operator=(const Ship&) = delete;
    Ship(Ship&&) = default;
    Ship& operator=(Ship&&) = default;

    void Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_SHIP_H
