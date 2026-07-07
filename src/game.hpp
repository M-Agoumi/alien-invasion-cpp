#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include "setting.hpp"
#include "sound_manager.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include "alien.hpp"
#include "explosion.hpp"
#include "drawer.hpp"
#include "level.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void process_input();
    void update();
    void draw();
    void check_collisions();
    void end_game();

    Setting setting;
    SoundManager sound_manager;
    Drawer drawer;

    Texture2D alien_texture;
    Texture2D explosion_texture;

    std::unique_ptr<PlayerShip> player;
    std::vector<Bullet> bullets;
    std::vector<Alien> aliens;
    std::vector<Explosion> explosions;

    Level level;
    bool was_paused;
};
