#pragma once

#include <string>
#include <vector>
#include <raylib.h>
#include "parser.hpp"

class Setting {
public:
    Setting();
    ~Setting();

    void init_screen(int width, int height);
    void load_resources();
    void unload_resources();
    
    void fill();
    void update_stars();
    void draw_stars();

    int get_screen_x() const { return screen_width; }
    int get_screen_y() const { return screen_height; }

    // Configuration data
    Color background_color;
    std::string window_description;
    
    int bullet_speed_factor;
    int bullet_width;
    int bullet_height;
    Color bullet_color;
    int bullet_allowed;
    
    int sf_ship_lives;
    int game_score;
    bool pause;

    // Assets loaded in VRAM
    Texture2D star_texture;
    Texture2D score_texture;
    Texture2D hp_texture;
    Texture2D ship_texture;
    Texture2D alien_texture;
    Texture2D explosion_texture;
    Texture2D player_texture;

private:
    Parser parser;
    int screen_width;
    int screen_height;
    std::vector<Vector2> stars;
};
