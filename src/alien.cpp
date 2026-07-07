#include "alien.hpp"
#include <iostream>

Alien::Alien(Texture2D tex, float speed_factor, int screen_w, int screen_h)
    : Ship(tex, speed_factor, screen_w, screen_h) {
    ship_hp = 100;
    move_down_accum = 0.0f;
    last_firing_time = GetTime() - GetRandomValue(0, 3000) / 1000.0;
    place_ship();

    if (GetRandomValue(0, 1) == 1) {
        moving_right = true;
        moving_left = false;
    } else {
        moving_right = false;
        moving_left = true;
    }
}

void Alien::place_ship() {
    int max_x = screen_w - texture.width;
    x = (max_x > 0) ? GetRandomValue(0, max_x) : 0;
    y = -100;
}

void Alien::update_hp(int hp) {
    ship_hp -= hp;
}

void Alien::update_alien(std::vector<Bullet>& bullets, int bullet_w, int bullet_h, Color bullet_c, float bullet_speed) {
    // 1. Firing
    double current_time = GetTime();
    if ((current_time - last_firing_time) > 3.0) {
        float bullet_start_x = x + texture.width / 2.0f - 1.0f;
        float bullet_start_y = y + 20.0f;
        bullets.push_back(Bullet(bullet_w, bullet_h, bullet_c, bullet_speed, bullet_start_x, bullet_start_y, false));
        last_firing_time = current_time;
    }

    // 2. Horizontal movement & screen boundary bouncing
    if (moving_right && (x + texture.width) >= screen_w) {
        moving_right = false;
        moving_left = true;
    }
    if (moving_left && x <= 0) {
        moving_right = true;
        moving_left = false;
    }

    if (moving_right) {
        x += speed_factor;
    } else if (moving_left) {
        x -= speed_factor;
    }

    // 3. Vertical drift down toward the player
    if (y > 20.0f) {
        speed_factor = 1.0f;
    }

    move_down_accum += 10.0f * speed_factor;
    if (move_down_accum >= 100.0f) {
        y += 1.0f;
        move_down_accum = 0.0f;
    }
}
