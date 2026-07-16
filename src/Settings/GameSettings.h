//
// Created by Magoumi on 7/16/2026.
//
// Central, game-wide configuration. Holds every player-configurable value
// (audio, video, window, ...) in ONE place so screens and managers share a
// single source of truth instead of each keeping their own copy.
//
// It's a singleton: access the one shared instance via GameSettings::Get().
//   float v = GameSettings::Get().musicVolume;
//   GameSettings::Get().musicVolume = 0.5f;
//

#ifndef ALIENINVASION_GAMESETTINGS_H
#define ALIENINVASION_GAMESETTINGS_H
#pragma once

class GameSettings
{
public:
    // ---- Audio ----
    float musicVolume = 0.25f; // 0.0 (silent) .. 1.0 (full). Default 25%.
    bool  musicMuted  = false;

    // ---- Video / performance ----
    // Target frames per second. 0 means "match the monitor's refresh rate"
    // (the engine will query it at startup).
    int  targetFps    = 0;
    bool fullscreen   = false;

    // ---- Window (windowed-mode dimensions) ----
    int windowWidth  = 1000;
    int windowHeight = 800;

    // ---- Convenience helpers ----
    // Effective volume actually sent to the audio device (0 when muted).
    [[nodiscard]] float EffectiveVolume() const
    {
        return musicMuted ? 0.0f : musicVolume;
    }

    // Volume as a 0..100 percentage, handy for UI sliders / labels.
    [[nodiscard]] float VolumePercent() const { return musicVolume * 100.0f; }
    void SetVolumePercent(float percent)
    {
        if (percent < 0.0f)   percent = 0.0f;
        if (percent > 100.0f) percent = 100.0f;
        musicVolume = percent / 100.0f;
    }

    // ---- Singleton access ----
    static GameSettings& Get()
    {
        static GameSettings instance; // created once, lives for the whole run
        return instance;
    }

    // A single shared instance -> forbid copying/moving.
    GameSettings(const GameSettings&) = delete;
    GameSettings& operator=(const GameSettings&) = delete;
    GameSettings(GameSettings&&) = delete;
    GameSettings& operator=(GameSettings&&) = delete;

private:
    GameSettings() = default;
    ~GameSettings() = default;
};

#endif //ALIENINVASION_GAMESETTINGS_H

