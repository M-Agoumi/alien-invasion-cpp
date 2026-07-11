//
// Created by Magoumi on 7/10/2026.
//

#pragma once
#ifndef ALIENINVASION_SETTING_PAGE_H
#define ALIENINVASION_SETTING_PAGE_H
#include "Screen.h"
#include "../UI/Button.h"
#include "../UI/TextLabel.h"

class SettingPage : public Screen
{
    Button* btnBack;
    Button* btnFullscreen;
    Button* btnMute;
    TextLabel* titleLabel;
    bool isFullscreen;
    float volumeLevel;

public:
    SettingPage(); // Constructor
    ~SettingPage() override; // Destructor

    ScreenAction Update() override;
    void Draw() override;
};

#endif //ALIENINVASION_SETTING_PAGE_H
