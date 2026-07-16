//
// Created by Magoumi on 7/16/2026.
//

#include "SoundManager.h"

SoundManager::SoundManager()
{
    // Stream the track from disk (better than Sound for long music).
    backgroundMusic = LoadMusicStream(kBackgroundTrack);

    // LoadMusicStream returns a zeroed stream on failure; frameCount > 0
    // tells us the file actually loaded.
    loaded = backgroundMusic.frameCount > 0;

    if (loaded) {
        backgroundMusic.looping = true;
        SetBackgroundVolume(0.25f); // start at 25% volume
        PlayBackground();
    }
}

SoundManager::~SoundManager()
{
    if (loaded) {
        StopMusicStream(backgroundMusic);
        UnloadMusicStream(backgroundMusic);
        loaded = false;
    }
}

void SoundManager::Update()
{
    // Refills the audio buffer; must run every frame while music plays.
    if (loaded) {
        UpdateMusicStream(backgroundMusic);
    }
}

void SoundManager::PlayBackground()
{
    if (loaded) {
        PlayMusicStream(backgroundMusic);
    }
}

void SoundManager::StopBackground()
{
    if (loaded) {
        StopMusicStream(backgroundMusic);
    }
}

void SoundManager::SetBackgroundVolume(float volume)
{
    if (loaded) {
        SetMusicVolume(backgroundMusic, volume);
    }
}

