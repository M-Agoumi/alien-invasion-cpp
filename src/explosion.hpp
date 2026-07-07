#pragma once
#include <raylib.h>

class Explosion {
public:
    Explosion(Texture2D sheet, float x, float y);

    void update();
    void draw() const;
    bool is_finished() const;

private:
    Texture2D sheet;
    float x;
    float y;
    double created_time; // in seconds
    int current_frame;
};
