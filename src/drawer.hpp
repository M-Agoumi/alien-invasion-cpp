#pragma once
#include <raylib.h>
#include <string>
#include <vector>

struct MessageInfo {
    std::string text;
    double timestamp; // in seconds
};

class Setting;

class Drawer {
public:
    Drawer(Setting* setting);

    void draw_game_info(int fps, int hp, int lives);
    void add_message(const std::string& msg);
    void adjust_messages_for_paused_time(double paused_duration);
    void draw_messages();
    void draw_pause();

    void draw_text_with_outline(const std::string& text, int font_size, int x, int y, 
                                Color text_color, Color outline_color, 
                                Color bg_color = BLANK, int padding = 0);

private:
    Setting* setting;
    std::vector<MessageInfo> messages;
};
