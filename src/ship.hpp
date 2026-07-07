#pragma once
#include <raylib.h>

class Ship {
public:
    Ship(Texture2D tex, float speed_factor, int screen_w, int screen_h);
    virtual ~Ship();

    virtual void place_ship() = 0;
    virtual void update_hp(int hp) = 0;
    int get_hp() const { return ship_hp; }

    virtual void update();
    virtual void draw() const;

    Rectangle get_rect() const { 
        return Rectangle{ x, y, (float)texture.width, (float)texture.height }; 
    }

    float x;
    float y;
    float speed_factor;
    int ship_hp;

    bool moving_right;
    bool moving_left;

protected:
    Texture2D texture;
    int screen_w;
    int screen_h;
};

class PlayerShip : public Ship {
public:
    PlayerShip(Texture2D tex, float speed_factor, int screen_w, int screen_h);
    void place_ship() override;
    void update_hp(int hp) override;
    void post_die();
};

