#include "drawer.hpp"
#include "setting.hpp"
#include <iostream>

Drawer::Drawer(Setting* setting) : setting(setting) {
}

void Drawer::draw_game_info(int fps, int hp, int lives) {
    // 1. Draw Score
    if (setting->score_texture.id > 0) {
        DrawTexture(setting->score_texture, 10, 10, WHITE);
    }
    std::string score_str = std::to_string(setting->game_score);
    DrawText(score_str.c_str(), 45, 15, 20, WHITE);

    // 2. Draw HP
    if (setting->hp_texture.id > 0) {
        DrawTexture(setting->hp_texture, 10, 45, WHITE);
    }
    std::string hp_str = std::to_string(hp);
    DrawText(hp_str.c_str(), 45, 48, 20, WHITE);

    // 3. Draw Lives
    if (setting->ship_texture.id > 0) {
        DrawTexture(setting->ship_texture, 10, 80, WHITE);
    }
    std::string lives_str = std::to_string(lives);
    DrawText(lives_str.c_str(), 45, 90, 20, WHITE);

    // 4. Draw FPS in top right corner
    std::string fps_str = std::to_string(fps);
    int fps_w = MeasureText(fps_str.c_str(), 20);
    DrawText(fps_str.c_str(), setting->get_screen_x() - fps_w - 10, 10, 20, RED);

    // 5. Draw active timeline messages
    draw_messages();
}

void Drawer::add_message(const std::string& msg) {
    messages.push_back({msg, GetTime()});
}

void Drawer::adjust_messages_for_paused_time(double paused_duration) {
    for (auto& msg : messages) {
        msg.timestamp += paused_duration;
    }
}

void Drawer::draw_messages() {
    double current_time = GetTime();
    for (auto it = messages.begin(); it != messages.end(); ) {
        if (current_time - it->timestamp > 3.0) {
            it = messages.erase(it);
        } else {
            int font_size = 80;
            int text_width = MeasureText(it->text.c_str(), font_size);
            int x = (setting->get_screen_x() - text_width) / 2;
            int y = (setting->get_screen_y() - font_size) / 2;
            draw_text_with_outline(it->text, font_size, x, y, WHITE, BLUE);
            ++it;
        }
    }
}

void Drawer::draw_pause() {
    int font_size = 75;
    int text_width = MeasureText("PAUSE", font_size);
    int x = (setting->get_screen_x() - text_width) / 2;
    int y = (setting->get_screen_y() - font_size) / 2;
    Color bg_color = {50, 50, 50, 220};
    draw_text_with_outline("PAUSE", font_size, x, y, WHITE, BLUE, bg_color, 20);
}

void Drawer::draw_text_with_outline(const std::string& text, int font_size, int x, int y, 
                                    Color text_color, Color outline_color, 
                                    Color bg_color, int padding) {
    int text_width = MeasureText(text.c_str(), font_size);
    int text_height = font_size;

    if (bg_color.a > 0) {
        Rectangle bg_rect = { (float)x - padding, (float)y - padding, (float)text_width + padding * 2, (float)text_height + padding * 2 };
        DrawRectangleRec(bg_rect, bg_color);
    }

    // Outer offsets for outline
    DrawText(text.c_str(), x - 1, y - 1, font_size, outline_color);
    DrawText(text.c_str(), x + 1, y - 1, font_size, outline_color);
    DrawText(text.c_str(), x - 1, y + 1, font_size, outline_color);
    DrawText(text.c_str(), x + 1, y + 1, font_size, outline_color);
    
    // Core text
    DrawText(text.c_str(), x, y, font_size, text_color);
}
