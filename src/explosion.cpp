#include "explosion.hpp"

Explosion::Explosion(Texture2D sheet, float x, float y)
    : sheet(sheet), x(x), y(y) {
    created_time = GetTime();
    current_frame = 0;
}

void Explosion::update() {
    double elapsed_seconds = GetTime() - created_time;
    int elapsed_ms = (int)(elapsed_seconds * 1000.0);
    current_frame = elapsed_ms / 50; // 50ms per frame
    if (current_frame >= 45) {
        current_frame = 44;
    }
}

void Explosion::draw() const {
    if (sheet.id > 0) {
        // Cut out current frame from single-row sprite sheet (each frame is 250x250)
        Rectangle source = { (float)current_frame * 250.0f, 0.0f, 250.0f, 250.0f };
        // Output coordinates resized to 75x75 on the screen
        Rectangle dest = { x, y, 75.0f, 75.0f };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(sheet, source, dest, origin, 0.0f, WHITE);
    }
}

bool Explosion::is_finished() const {
    return (GetTime() - created_time) >= 2.0; // Ends after 2000ms
}
