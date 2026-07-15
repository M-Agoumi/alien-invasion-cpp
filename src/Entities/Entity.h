//
// Created by Magoumi on 7/15/2026.
//

#pragma once
#ifndef ALIENINVASION_ENTITY_H
#define ALIENINVASION_ENTITY_H

class Entity
{
public:
    virtual ~Entity() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif //ALIENINVASION_ENTITY_H
