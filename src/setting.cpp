#include "setting.hpp"
#include <iostream>

Setting::Setting() {
    ConfigData cfg = parser.parse_config();
    window_description = cfg.game_window.description;

    auto bg = cfg.game_window.background;
    if (bg.size() >= 3) {
        background_color = Color{(unsigned char)bg[0], (unsigned char)bg[1], (unsigned char)bg[2], 255};
    } else {
        background_color = Color{20, 20, 20, 255};
    }

    bullet_speed_factor = cfg.bullet.speed_factor;
    bullet_width = cfg.bullet.width;
    bullet_height = cfg.bullet.height;

    auto bc = cfg.bullet.color;
    if (bc.size() >= 3) {
        bullet_color = Color{(unsigned char)bc[0], (unsigned char)bc[1], (unsigned char)bc[2], 255};
    } else {
        bullet_color = Color{200, 200, 200, 255};
    }

    bullet_allowed = cfg.bullet.allowed_number;
    sf_ship_lives = cfg.game_specs.lives;

    game_score = 0;
    pause = false;
    screen_width = 0;
    screen_height = 0;

    star_texture = {0};
    score_texture = {0};
    hp_texture = {0};
    ship_texture = {0};
    alien_texture = {0};
    explosion_texture = {0};
    player_texture = {0};
}

Setting::~Setting() {
    unload_resources();
    if (IsWindowReady()) {
        CloseWindow();
    }
}

void Setting::init_screen(int width, int height) {
    screen_width = width;
    screen_height = height;

    InitWindow(width, height, window_description.c_str());
    ToggleFullscreen();

    // Set application window icon
    Image icon = LoadImage("icon.jpeg");
    if (icon.data != nullptr) {
        SetWindowIcon(icon);
        UnloadImage(icon);
    }
}

void Setting::load_resources() {
    // Load BMPs as Images
    Image star_img = LoadImage("resources/images/star_01.bmp");
    Image score_img = LoadImage("resources/images/score_icon.bmp");
    Image hp_img = LoadImage("resources/images/heart.bmp");
    Image ship_img = LoadImage("resources/images/spaceship_icon.bmp");
    Image alien_img = LoadImage("resources/images/alien_1.bmp");
    Image explosion_img = LoadImage("resources/images/explosion/animation.bmp");
    Image player_img = LoadImage("resources/images/spaceship_1.bmp");

    // Scale them to correct sizing
    if (star_img.data) ImageResize(&star_img, 25, 25);
    if (score_img.data) ImageResize(&score_img, 25, 25);
    if (hp_img.data) ImageResize(&hp_img, 25, 25);
    if (ship_img.data) ImageResize(&ship_img, 25, 40);
    if (alien_img.data) ImageResize(&alien_img, 60, 70);
    if (player_img.data) ImageResize(&player_img, 50, 80);

    // Upload images to VRAM (GPU textures)
    if (star_img.data) star_texture = LoadTextureFromImage(star_img);
    if (score_img.data) score_texture = LoadTextureFromImage(score_img);
    if (hp_img.data) hp_texture = LoadTextureFromImage(hp_img);
    if (ship_img.data) ship_texture = LoadTextureFromImage(ship_img);
    if (alien_img.data) alien_texture = LoadTextureFromImage(alien_img);
    if (explosion_img.data) explosion_texture = LoadTextureFromImage(explosion_img);
    if (player_img.data) player_texture = LoadTextureFromImage(player_img);

    // Clean up CPU-side images
    UnloadImage(star_img);
    UnloadImage(score_img);
    UnloadImage(hp_img);
    UnloadImage(ship_img);
    UnloadImage(alien_img);
    UnloadImage(explosion_img);
    UnloadImage(player_img);
}

void Setting::unload_resources() {
    if (star_texture.id > 0) UnloadTexture(star_texture);
    if (score_texture.id > 0) UnloadTexture(score_texture);
    if (hp_texture.id > 0) UnloadTexture(hp_texture);
    if (ship_texture.id > 0) UnloadTexture(ship_texture);
    if (alien_texture.id > 0) UnloadTexture(alien_texture);
    if (explosion_texture.id > 0) UnloadTexture(explosion_texture);
    if (player_texture.id > 0) UnloadTexture(player_texture);
}

void Setting::fill() {
    ClearBackground(background_color);
    draw_stars();
}

void Setting::update_stars() {
    if (stars.empty()) {
        for (int i = 0; i < 100; ++i) {
            float x = GetRandomValue(0, screen_width);
            float y = GetRandomValue(0, screen_height);
            stars.push_back(Vector2{x, y});
        }
    } else {
        for (auto& star : stars) {
            star.y += 1.0f; // Star scroll speed
            if (star.y > screen_height) {
                star.x = GetRandomValue(0, screen_width);
                star.y = -20;
            }
        }
    }
}

void Setting::draw_stars() {
    for (const auto& star : stars) {
        if (star_texture.id > 0) {
            DrawTexture(star_texture, (int)star.x, (int)star.y, WHITE);
        }
    }
}
