#pragma once
#include <raylib.h>

class Bullet {
public:
    Bullet(int width, int height, Color color, float speed_factor, float start_x, float start_y, bool friendly);

    void update();
    void draw() const;

    bool is_friendly() const { return friendly_flag; }
    Rectangle get_rect() const { return Rectangle{ x, y, (float)width, (float)height }; }

    float x;
    float y;

private:
    int width;
    int height;
    Color color;
    float speed_factor;
    bool friendly_flag;
};
