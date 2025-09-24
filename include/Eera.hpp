#pragma once
#include "raylib.h"
#include <string>

class Eera {
public:
    Eera();
    ~Eera();

    void update(float deltaTime);
    void draw() const;

private:
    Texture2D textureIdle;
    Texture2D textureRight;
    Texture2D textureLeft;
    Rectangle frameRec;
    int frameCount;
    int currentFrame;
    float frameTime;
    float timer;

    Vector2 position;
    Vector2 velocity;
    float speed;

    // Jump
    bool isJumping;
    float jumpVelocity;
    float gravity;
    float verticalVelocity;
    bool onGround;

    // Variable jump
    float maxJumpTime;
    float jumpTime;
    bool jumpHeld;

    std::string name;
};
