#include "sound_manager.hpp"

SoundManager::SoundManager() : audio_initialized(false) {
    bg_music = {0};
    lazer_sound = {0};
    explosion_sound = {0};
    warp_sound = {0};
}

void SoundManager::init() {
    if (audio_initialized) return;

    InitAudioDevice();
    if (IsAudioDeviceReady()) {
        audio_initialized = true;
        bg_music = LoadMusicStream("resources/sounds/moonlightsonataspace.ogg");
        SetMusicVolume(bg_music, 0.5f);
        PlayMusicStream(bg_music);

        lazer_sound = LoadSound("resources/sounds/laser_shot_sound_lazer.wav");
        SetSoundVolume(lazer_sound, 0.20f);

        explosion_sound = LoadSound("resources/sounds/explosion.wav");
        SetSoundVolume(explosion_sound, 0.25f);

        warp_sound = LoadSound("resources/sounds/drop-out-warp.wav");
        SetSoundVolume(warp_sound, 1.0f);
    }
}

SoundManager::~SoundManager() {
    if (audio_initialized) {
        UnloadMusicStream(bg_music);
        UnloadSound(lazer_sound);
        UnloadSound(explosion_sound);
        UnloadSound(warp_sound);
        CloseAudioDevice();
    }
}

void SoundManager::update() {
    if (audio_initialized) {
        UpdateMusicStream(bg_music);
    }
}

void SoundManager::shot_lazer() {
    if (audio_initialized) {
        PlaySound(lazer_sound);
    }
}

void SoundManager::destroy_ship() {
    if (audio_initialized) {
        PlaySound(explosion_sound);
    }
}

void SoundManager::warp_out() {
    if (audio_initialized) {
        PlaySound(warp_sound);
    }
}
