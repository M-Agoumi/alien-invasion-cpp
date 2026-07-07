#include "ship.hpp"

Ship::Ship(Texture2D tex, float speed_factor, int screen_w, int screen_h)
    : texture(tex), speed_factor(speed_factor), screen_w(screen_w), screen_h(screen_h) {
    x = 0;
    y = 0;
    ship_hp = 100;
    moving_right = false;
    moving_left = false;
}

Ship::~Ship() {
    // Texture is managed by Setting/Game to avoid double free
}

void Ship::update() {
    if (moving_right && (x + texture.width) < screen_w) {
        x += speed_factor;
    }
    if (moving_left && x > 0) {
        x -= speed_factor;
    }
}

void Ship::draw() const {
    if (texture.id > 0) {
        DrawTexture(texture, (int)x, (int)y, WHITE);
    }
}

PlayerShip::PlayerShip(Texture2D tex, float speed_factor, int screen_w, int screen_h)
    : Ship(tex, speed_factor, screen_w, screen_h) {
    place_ship();
}

void PlayerShip::place_ship() {
    x = (screen_w - texture.width) / 2.0f;
    y = (screen_h - texture.height);
}

void PlayerShip::update_hp(int hp) {
    ship_hp -= hp;
}

void PlayerShip::post_die() {
    ship_hp = 100;
}

