#include "Eera.hpp"
#include <raymath.h>

Eera::Eera() {
    textureIdle = LoadTexture("assets/idle.png");
    textureRight = LoadTexture("assets/right_move.png");
    textureLeft = LoadTexture("assets/left_move.png");

    frameCount = 4;
    int frameWidth = textureIdle.width / frameCount;
    frameRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(textureIdle.height) };
    frameTime = 0.3f;
    timer = 0.0f;
    currentFrame = 0;

    position = {
        GetScreenWidth() / 2.0f - frameRec.width / 2.0f,
        GetScreenHeight() - frameRec.height
    };

    velocity = { 0.0f, 0.0f };
    speed = 250.0f;

    isJumping = false;
    jumpVelocity = -400.0f;
    gravity = 1200.0f;
    verticalVelocity = 0.5f;
    onGround = true;

    maxJumpTime = 0.25f;
    jumpTime = 0.0f;
    jumpHeld = false;

    name = "Eera";
}

Eera::~Eera() {
    UnloadTexture(textureIdle);
    UnloadTexture(textureRight);
    UnloadTexture(textureLeft);
}

void Eera::update(float deltaTime) {
    // Animate
    timer += deltaTime;
    if (timer >= frameTime) {
        currentFrame = (currentFrame + 1) % frameCount;
        timer = 0.0f;
    }

    // Horizontal movement
    velocity.x = 0.0f;
    if (IsKeyDown(KEY_LEFT))  velocity.x = -speed;
    if (IsKeyDown(KEY_RIGHT)) velocity.x = speed;

    // Jump initiation
    if (onGround && IsKeyPressed(KEY_S)) {
        verticalVelocity = jumpVelocity;
        isJumping = true;
        onGround = false;
        jumpHeld = true;
        jumpTime = 0.0f;

        if (IsKeyDown(KEY_LEFT))  velocity.x = -speed * 0.6f;
        if (IsKeyDown(KEY_RIGHT)) velocity.x = speed * 0.6f;
    }

    // Jump hold logic
    if (isJumping && jumpHeld && IsKeyDown(KEY_S)) {
        jumpTime += deltaTime;
        if (jumpTime < maxJumpTime) {
            verticalVelocity = jumpVelocity;
        }
        else {
            jumpHeld = false;
        }
    }

    // Early release
    if (isJumping && IsKeyReleased(KEY_S)) {
        jumpHeld = false;
    }

    // Gravity
    if (!onGround) {
        verticalVelocity += gravity * deltaTime;
        position.y += verticalVelocity * deltaTime;

        float groundY = GetScreenHeight() - frameRec.height;
        if (position.y >= groundY) {
            position.y = groundY;
            verticalVelocity = 0.0f;
            isJumping = false;
            onGround = true;
            jumpHeld = false;
        }
    }

    // Apply horizontal movement
    position.x += velocity.x * deltaTime;

    // Clamp to screen
    position.x = Clamp(position.x, 0.0f, GetScreenWidth() - frameRec.width);

    // Update frameRec.x based on current frame
    frameRec.x = currentFrame * frameRec.width;
}

void Eera::draw() const {
    Texture2D currentTexture = textureIdle;
    if (velocity.x > 0) currentTexture = textureRight;
    else if (velocity.x < 0) currentTexture = textureLeft;

    DrawTextureRec(currentTexture, frameRec, position, WHITE);
}
