#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include "parser.hpp"
#include "alien.hpp"
#include "drawer.hpp"
#include "sound_manager.hpp"

class Level {
public:
    Level(Setting* setting, Drawer* drawer, SoundManager* sound_manager, 
          std::vector<Alien>& aliens);

    void play_level();
    void pause_time_start();
    void pause_time_stop();
    int get_current_level_num() const { return level_num; }

private:
    void init_scene();
    void parse_scene();
    void play_scene();
    bool get_current_event(LevelEvent& out_event);
    void play_scene_message(const LevelEvent& ev);
    void play_spawn(const LevelEvent& ev);
    void play_scene_end();
    void spawn_ship(const SpawnInfo& spawn);

    Setting* setting;
    Drawer* drawer;
    SoundManager* sound_manager;
    std::vector<Alien>& aliens;

    int level_num;
    std::vector<LevelEvent> scene_events;
    bool level_ended;

    double level_start_time;       // In seconds
    double pause_start_time;       // In seconds
    double total_paused_duration;  // In seconds
};
