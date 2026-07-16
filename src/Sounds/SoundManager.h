//
// Created by Magoumi on 7/16/2026.
//

#ifndef ALIENINVASION_SOUNDMANAGER_H
#define ALIENINVASION_SOUNDMANAGER_H
#pragma once

#include "raylib.h"

// Central place for the game's audio. Right now it streams a single
// looping background track, but it's designed so sound effects can be
// added later without touching the rest of the game.
//
// NOTE: An audio device must already be initialized (InitAudioDevice())
// before a SoundManager is constructed, since it loads a music stream.
class SoundManager
{
public:
    // Loads the background music and starts it looping immediately.
    SoundManager();
    ~SoundManager();

    // Owns a streaming audio resource -> forbid copying (rule of five).
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    SoundManager(SoundManager&&) = default;
    SoundManager& operator=(SoundManager&&) = default;

    // Must be called once per frame to keep the music stream fed.
    void Update();

    void PlayBackground();
    void StopBackground();
    void SetBackgroundVolume(float volume); // 0.0f (silent) .. 1.0f (full)

private:
    Music backgroundMusic{};
    bool loaded = false;

    static constexpr const char* kBackgroundTrack =
        "resources/sounds/moonlightsonataspace.ogg";
};

#endif //ALIENINVASION_SOUNDMANAGER_H

