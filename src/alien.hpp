#pragma once
#include "ship.hpp"
#include "bullet.hpp"
#include <vector>

class Alien : public Ship {
public:
    Alien(Texture2D tex, float speed_factor, int screen_w, int screen_h);

    void place_ship() override;
    void update_hp(int hp) override;

    // Custom update method since it needs to fire bullets and handle special vertical drift
    void update_alien(std::vector<Bullet>& bullets, int bullet_w, int bullet_h, Color bullet_c, float bullet_speed);

private:
    double last_firing_time;
    float move_down_accum;
};
