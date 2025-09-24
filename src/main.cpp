#include "raylib.h"
#include "Eera.hpp"

enum GameState { MENU, PLAY };
GameState currentState = MENU;

bool paused = false;

int selectedOption = 0;
const char* menuItems[] = { "New Game", "Continue", "Exit" };
const int menuCount = 3;

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "InkLand");
    SetTargetFPS(60);
    Color canvas = { 191, 192, 187, 255 };

    Eera eera;

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        // TAB toggles pause
        if (currentState == PLAY && IsKeyPressed(KEY_TAB)) {
            paused = !paused;
        }

        // Menu logic
        if (currentState == MENU) {
            if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % menuCount;
            if (IsKeyPressed(KEY_UP))   selectedOption = (selectedOption - 1 + menuCount) % menuCount;

            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedOption == 0) currentState = PLAY;
                if (selectedOption == 1) {/* we yap later */ }
                if (selectedOption == 2) break;
            }
        }
        // Game logic
        else if (currentState == PLAY && !paused) {
            eera.update(delta);
        }
        // Pause logic
        else if (currentState == PLAY && paused) {
            if (IsKeyPressed(KEY_ENTER)) {
                break;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(canvas);

        if (currentState == MENU) {
            ClearBackground(BLACK);
            DrawText("InkLand", 520, 180, 60, LIGHTGRAY);
            DrawText("The last stroke", 540, 240, 20, GRAY);

            for (int i = 0; i < menuCount; i++) {
                Color color = (i == selectedOption) ? WHITE : GRAY;
                DrawText(menuItems[i], 560, 320 + i * 40, 30, color);
            }
        }
        else if (currentState == PLAY) {
            eera.draw();
            DrawText("<- ->   Move", 20, 20, 20, BLACK);
            DrawText("S        Jump", 20, 45, 20, BLACK);
            DrawText("Tab      Pause", 20, 70, 20, BLACK);

            if (paused) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));

                DrawText("Paused", 560, 200, 40, WHITE);

                DrawText("Press Enter to Exit", 500, 260, 20, LIGHTGRAY);
            }

        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
