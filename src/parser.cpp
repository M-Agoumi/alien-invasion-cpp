#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

static std::vector<int> parse_list(const std::string& val) {
    std::vector<int> res;
    size_t start = val.find('[');
    size_t end = val.find(']');
    if (start != std::string::npos && end != std::string::npos && end > start) {
        std::string sub = val.substr(start + 1, end - start - 1);
        std::stringstream ss(sub);
        std::string item;
        while (std::getline(ss, item, ',')) {
            try {
                res.push_back(std::stoi(trim(item)));
            } catch (...) {}
        }
    }
    return res;
}

ConfigData Parser::parse_config() {
    ConfigData data;
    std::ifstream file("config/config.yaml");
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open config/config.yaml, using defaults." << std::endl;
        return data;
    }

    std::string line;
    std::string current_section = "";

    while (std::getline(file, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#') {
            continue;
        }

        // Check for sections
        if (trimmed.back() == ':') {
            current_section = trim(trimmed.substr(0, trimmed.size() - 1));
            continue;
        }

        // Parse key-value pairs
        size_t colon_pos = trimmed.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = trim(trimmed.substr(0, colon_pos));
            std::string val = trim(trimmed.substr(colon_pos + 1));

            // Strip quotes if present
            if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                val = val.substr(1, val.size() - 2);
            }

            if (current_section == "game_window") {
                if (key == "description") data.game_window.description = val;
                else if (key == "background") data.game_window.background = parse_list(val);
            } else if (current_section == "bullet") {
                if (key == "speed_factor") data.bullet.speed_factor = std::stoi(val);
                else if (key == "width") data.bullet.width = std::stoi(val);
                else if (key == "height") data.bullet.height = std::stoi(val);
                else if (key == "color") data.bullet.color = parse_list(val);
                else if (key == "allowed_number") data.bullet.allowed_number = std::stoi(val);
            } else if (current_section == "game_specs") {
                if (key == "lives") data.game_specs.lives = std::stoi(val);
            }
        }
    }

    return data;
}

std::vector<LevelEvent> Parser::parse_level(const std::string& level_num) {
    std::string path = "levels/level_" + level_num + ".json";
    std::ifstream file(path);
    std::vector<LevelEvent> events;
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << path << std::endl;
        return events;
    }

    nlohmann::json root;
    try {
        file >> root;
        if (root.contains("events") && root["events"].is_array()) {
            for (const auto& ev : root["events"]) {
                LevelEvent event;
                event.type = ev.value("type", "");
                event.timestamp = ev.value("timestamp", 0);

                if (ev.contains("content")) {
                    if (ev["content"].is_string()) {
                        event.message_content = ev["content"].get<std::string>();
                    } else if (ev["content"].is_array()) {
                        // Level 1 spawn list
                        for (const auto& sp : ev["content"]) {
                            SpawnInfo spawn;
                            spawn.ship = sp.value("ship", "");
                            spawn.type = sp.value("type", "enemy");
                            spawn.position = sp.value("position", "random");
                            spawn.level = sp.value("level", 1);
                            spawn.speed = sp.value("speed", 1.0f);
                            event.spawns.push_back(spawn);
                        }
                    } else if (ev["content"].is_object()) {
                        // Level 2 scene/spawn dictionary
                        const auto& content = ev["content"];
                        if (content.contains("spawn") && content["spawn"].is_array()) {
                            for (const auto& sp : content["spawn"]) {
                                SpawnInfo spawn;
                                spawn.ship = sp.value("ship", "");
                                spawn.type = sp.value("type", "enemy"); // defaults to enemy
                                spawn.position = sp.value("position", "random");
                                spawn.level = sp.value("level", 1);
                                spawn.speed = sp.value("speed", 1.0f);
                                event.spawns.push_back(spawn);
                            }
                        }
                    }
                }

                // Treat scene events as spawn events
                if (event.type == "scene") {
                    event.type = "spawn";
                }

                events.push_back(event);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing level file: " << e.what() << std::endl;
    }

    return events;
}
