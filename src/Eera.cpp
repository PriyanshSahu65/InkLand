#include "Eera.hpp"
#include <raymath.h>

Eera::Eera() {
    texture = LoadTexture("assets/idle.png");
    frameCount = 4;
    int frameWidth = texture.width / frameCount;
    frameRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(texture.height) };
    frameTime = 0.3f;
    timer = 0.0f;
    currentFrame = 0;

    position = {
        GetScreenWidth() / 2.0f - frameRec.width / 2.0f,
        GetScreenHeight() - frameRec.height
    };

    velocity = { 0.0f, 0.0f };
    speed = 200.0f;

    name = "Eera";
}

Eera::~Eera() {
    UnloadTexture(texture);
}

void Eera::update(float deltaTime) {
    // Animate
    timer += deltaTime;
    if (timer >= frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;
        frameRec.x = currentFrame * frameRec.width;
        timer = 0.0f;
    }

    // Movement
    velocity.x = 0.0f;
    if (IsKeyDown(KEY_LEFT))  velocity.x = -speed;
    if (IsKeyDown(KEY_RIGHT)) velocity.x = speed;

    position.x += velocity.x * deltaTime;

    // Clamp to screen
    position.x = Clamp(position.x, 0.0f, GetScreenWidth() - frameRec.width);
}

void Eera::draw() const {
    DrawTextureRec(texture, frameRec, position, WHITE);
}
