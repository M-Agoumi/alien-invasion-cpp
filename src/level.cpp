#include "level.hpp"
#include "setting.hpp"
#include <iostream>

Level::Level(Setting* setting, Drawer* drawer, SoundManager* sound_manager, 
             std::vector<Alien>& aliens)
    : setting(setting), drawer(drawer), sound_manager(sound_manager),
      aliens(aliens) {
    level_num = 1;
    level_ended = false;
    level_start_time = GetTime();
    pause_start_time = 0.0;
    total_paused_duration = 0.0;
}

void Level::play_level() {
    if (scene_events.empty() && !level_ended) {
        init_scene();
    }
    play_scene();
}

void Level::init_scene() {
    parse_scene();
}

void Level::parse_scene() {
    Parser parser;
    std::string lvl_str = (level_num < 10 ? "0" : "") + std::to_string(level_num);
    scene_events = parser.parse_level(lvl_str);

    // Reset timers
    level_start_time = GetTime();
    pause_start_time = 0.0;
    total_paused_duration = 0.0;
    level_ended = false;
}

void Level::play_scene() {
    if (level_ended) {
        play_scene_end();
        return;
    }

    LevelEvent ev;
    if (get_current_event(ev)) {
        if (ev.type == "message") {
            play_scene_message(ev);
        } else if (ev.type == "spawn") {
            play_spawn(ev);
        } else if (ev.type == "end") {
            level_ended = true;
        }
    }
}

bool Level::get_current_event(LevelEvent& out_event) {
    if (scene_events.empty()) {
        return false;
    }

    double current_time = GetTime();
    double time_elapsed = (current_time - level_start_time - total_paused_duration) * 1000.0;

    std::cout << "DEBUG: level_num=" << level_num 
              << ", current=" << current_time 
              << ", start=" << level_start_time 
              << ", elapsed=" << time_elapsed 
              << ", front_ts=" << scene_events.front().timestamp 
              << std::endl;

    if (time_elapsed > scene_events.front().timestamp) {
        out_event = scene_events.front();
        scene_events.erase(scene_events.begin());
        return true;
    }

    return false;
}

void Level::play_scene_message(const LevelEvent& ev) {
    std::cout << "displaying message: " << ev.message_content << std::endl;
    drawer->add_message(ev.message_content);
}

void Level::play_spawn(const LevelEvent& ev) {
    // Port fix: Spawn ALL ships in the spawn event, not just the first one!
    for (const auto& spawn_info : ev.spawns) {
        if (spawn_info.type == "enemy") {
            spawn_ship(spawn_info);
        }
    }
}

void Level::pause_time_start() {
    if (pause_start_time == 0.0) {
        pause_start_time = GetTime();
    }
}

void Level::pause_time_stop() {
    if (pause_start_time != 0.0) {
        double paused_duration = GetTime() - pause_start_time;
        total_paused_duration += paused_duration;
        
        // Adjust message fade timer
        drawer->adjust_messages_for_paused_time(paused_duration);
        
        pause_start_time = 0.0;
    }
}

void Level::spawn_ship(const SpawnInfo& spawn) {
    if (spawn.ship == "gravion") {
        Alien alien(setting->alien_texture, spawn.speed * 10.0f, setting->get_screen_x(), setting->get_screen_y());
        aliens.push_back(alien);
        sound_manager->warp_out();
    }
}

void Level::play_scene_end() {
    if (aliens.empty()) {
        drawer->add_message("Level complete");
        level_ended = false;

        // Move to the next level
        level_num++;
        std::string next_lvl_str = (level_num < 10 ? "0" : "") + std::to_string(level_num);
        std::string path = "levels/level_" + next_lvl_str + ".json";

        if (FileExists(path.c_str())) {
            parse_scene();
        } else {
            // No more levels: wrap around to level 1 and show game-wide completed message
            drawer->add_message("All Levels Completed!");
            level_num = 1;
            parse_scene();
        }
    }
}
