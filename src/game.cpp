#include "game.hpp"
#include <iostream>

Game::Game() 
    : drawer(&setting),
      level(&setting, &drawer, &sound_manager, aliens),
      was_paused(false) {
    
    // 1. Get system display monitor resolution
    int monitor = GetCurrentMonitor();
    int screen_w = GetMonitorWidth(monitor);
    int screen_h = GetMonitorHeight(monitor);
    
    // Fallback if monitor height/width queries return 0
    if (screen_w <= 0 || screen_h <= 0) {
        screen_w = 1200;
        screen_h = 800;
    }

    // 2. Initialize screen window and load global resources
    setting.init_screen(screen_w, screen_h);
    setting.load_resources();

    // 3. Initialize audio manager after screen window context is created
    sound_manager.init();

    // Regulate frame rate to match pygame monitor limits
    SetTargetFPS(165);

    // 4. Initialize player ship using the loaded shared textures
    player = std::make_unique<PlayerShip>(
        setting.player_texture, 
        2.0f, // Player speed factor (matches pygame warship setup)
        setting.get_screen_x(), 
        setting.get_screen_y()
    );
}

Game::~Game() {
    // setting's destructor handles CloseWindow() and UnloadTexture()
}

void Game::run() {
    while (!WindowShouldClose()) {
        process_input();

        if (setting.pause) {
            level.pause_time_start();
            was_paused = true;

            // Draw game screen paused state
            BeginDrawing();
            setting.fill();
            player->draw();
            for (const auto& bullet : bullets) bullet.draw();
            for (const auto& alien : aliens) alien.draw();
            for (const auto& explosion : explosions) explosion.draw();
            drawer.draw_pause();
            EndDrawing();
            
            // Keep background music running
            sound_manager.update();
            continue;
        } else if (was_paused) {
            was_paused = false;
            level.pause_time_stop();
        }

        update();
        draw();
    }
}

void Game::process_input() {
    // 1. Key check toggles
    if (IsKeyPressed(KEY_P)) {
        setting.pause = !setting.pause;
    }
    if (IsKeyPressed(KEY_Q)) {
        end_game();
    }

    // 2. Ship movement
    player->moving_right = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT));
    player->moving_left = (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));

    // 3. Laser weapon shooting
    if (IsKeyPressed(KEY_SPACE)) {
        int total_bullets = 0;
        for (const auto& b : bullets) {
            if (b.is_friendly()) total_bullets++;
        }
        if (total_bullets < setting.bullet_allowed) {
            float start_x = player->x + player->get_rect().width / 2.0f - setting.bullet_width / 2.0f;
            float start_y = player->y - 12.0f; // Friendly offset
            bullets.push_back(Bullet(
                setting.bullet_width,
                setting.bullet_height,
                setting.bullet_color,
                (float)setting.bullet_speed_factor,
                start_x,
                start_y,
                true
            ));
            sound_manager.shot_lazer();
        }
    }
}

void Game::update() {
    // 1. Scroll starfield background
    setting.update_stars();

    // 2. Move player spaceship
    player->update();

    // 3. Increment level scheduler
    level.play_level();

    // 4. Update audio buffer streams
    sound_manager.update();

    // 5. Update alien positions and automated firing patterns
    for (auto& alien : aliens) {
        alien.update_alien(
            bullets, 
            setting.bullet_width, 
            setting.bullet_height, 
            setting.bullet_color, 
            (float)setting.bullet_speed_factor
        );
    }

    // 6. Update bullet coordinates & clean up out-of-screen projectiles
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->update();
        if (it->y < 0 || it->y > setting.get_screen_y()) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    // 7. Update frame steps of active explosions
    for (auto it = explosions.begin(); it != explosions.end(); ) {
        it->update();
        if (it->is_finished()) {
            it = explosions.erase(it);
        } else {
            ++it;
        }
    }

    // 8. Execute game collision matrices
    check_collisions();
}

void Game::check_collisions() {
    // 1. Collisions between bullets and aliens
    for (auto b_it = bullets.begin(); b_it != bullets.end(); ) {
        if (b_it->is_friendly()) {
            bool collided = false;
            for (auto a_it = aliens.begin(); a_it != aliens.end(); ) {
                if (CheckCollisionRecs(b_it->get_rect(), a_it->get_rect())) {
                    setting.game_score += 100;
                    sound_manager.destroy_ship();

                    // Center the 75x75 explosion on the alien ship
                    float exp_x = a_it->x + a_it->get_rect().width / 2.0f - 37.5f;
                    float exp_y = a_it->y + a_it->get_rect().height / 2.0f - 37.5f;
                    explosions.push_back(Explosion(setting.explosion_texture, exp_x, exp_y));

                    a_it = aliens.erase(a_it);
                    collided = true;
                } else {
                    ++a_it;
                }
            }
            if (collided) {
                b_it = bullets.erase(b_it);
            } else {
                ++b_it;
            }
        } else {
            // 2. Collisions between enemy lasers and player ship
            if (CheckCollisionRecs(b_it->get_rect(), player->get_rect())) {
                b_it = bullets.erase(b_it);
                player->update_hp(50);
                if (player->get_hp() <= 0) {
                    setting.sf_ship_lives -= 1;
                    player->post_die();
                }
                if (setting.sf_ship_lives <= 0) {
                    end_game();
                }
            } else {
                ++b_it;
            }
        }
    }
}

void Game::draw() {
    BeginDrawing();
    
    // Refresh background and stars
    setting.fill();

    // Draw player ship
    player->draw();

    // Draw active bullets
    for (const auto& bullet : bullets) {
        bullet.draw();
    }

    // Draw alien fleet
    for (const auto& alien : aliens) {
        alien.draw();
    }

    // Draw explosion particle arrays
    for (const auto& explosion : explosions) {
        explosion.draw();
    }

    // Draw HUD metrics
    drawer.draw_game_info(GetFPS(), player->get_hp(), setting.sf_ship_lives);

    EndDrawing();
}

void Game::end_game() {
    std::cout << "you died, and you have no life left, game over" << std::endl;
    exit(0);
}
