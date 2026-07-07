#include "bullet.hpp"

Bullet::Bullet(int width, int height, Color color, float speed_factor, float start_x, float start_y, bool friendly)
    : width(width), height(height), color(color), speed_factor(speed_factor), x(start_x), y(start_y), friendly_flag(friendly) {
}

void Bullet::update() {
    if (friendly_flag) {
        y -= speed_factor;
    } else {
        y += speed_factor;
    }
}

void Bullet::draw() const {
    DrawRectangle((int)x, (int)y, width, height, color);
}
