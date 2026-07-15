//
// Created by Magoumi on 7/15/2026.
//

#pragma once
#ifndef ALIENINVASION_SPACE_H
#define ALIENINVASION_SPACE_H
#include <vector>

#include "Entity.h"
#include "raylib.h"

struct BackgroundStar
{
    Vector2 position;
    float scale;
    Color tint; // Let us make some stars dimmer for depth!
};

class Space: public Entity
{
    Texture2D starTexture;
    // Our array (vector) of stars
    std::vector<BackgroundStar> stars;

    // Helper method to generate the field
    void GenerateStars();

public:
    Space();
    ~Space() override;

    // Space owns a GPU texture, so copying it would lead to a double-free /
    // dangling texture id (the source of the "star shows the ship" bug).
    // Forbid copying; allow moving instead.
    Space(const Space&) = delete;
    Space& operator=(const Space&) = delete;
    Space(Space&&) = default;
    Space& operator=(Space&&) = default;

    void Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_SPACE_H
