#pragma once
#include <raylib.h>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void init();   // Initialize audio device and load sound streams after InitWindow
    void update(); // Must be called once per frame to update bg music streaming
    void shot_lazer();
    void destroy_ship();
    void warp_out();

private:
    ::Music bg_music; // namespace-disambiguated to avoid conflict with class names
    Sound lazer_sound;
    Sound explosion_sound;
    Sound warp_sound;
    bool audio_initialized;
};
