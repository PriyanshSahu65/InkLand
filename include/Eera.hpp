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
    Texture2D texture;
    Rectangle frameRec;
    int frameCount;
    int currentFrame;
    float frameTime;
    float timer;

    Vector2 position;
    Vector2 velocity;
    float speed;

    //jump
    bool isJumping;
    float jumpVelocity;
    float gravity;
    float verticalVelocity;
    bool onGround;

    std::string name;
};
