#pragma once

#include <string>
#include <vector>

struct GameWindowConfig {
    std::string description = "Alien Invasion";
    std::vector<int> background = {20, 20, 20};
};

struct BulletConfig {
    int speed_factor = 4;
    int width = 3;
    int height = 15;
    std::vector<int> color = {200, 200, 200};
    int allowed_number = 3;
};

struct GameSpecsConfig {
    int lives = 3;
};

struct ConfigData {
    GameWindowConfig game_window;
    BulletConfig bullet;
    GameSpecsConfig game_specs;
};

struct SpawnInfo {
    std::string ship;
    std::string type = "enemy";
    std::string position; // "left", "right", "middle", "random"
    int level = 1;
    float speed = 1.0f;
};

struct LevelEvent {
    std::string type; // "message", "spawn", "scene", "end"
    int timestamp;    // in milliseconds
    std::string message_content;
    std::vector<SpawnInfo> spawns;
};

class Parser {
public:
    ConfigData parse_config();
    std::vector<LevelEvent> parse_level(const std::string& level_num);
};
