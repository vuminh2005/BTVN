#include <bits/stdc++.h>
#include <raylib.h>
#include "game.h"

using namespace std;

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(800, 1200, "Tetris");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false) {
        game.HandleInput();
        if (EventTriggered(1)) game.MoveBlockDown();
        BeginDrawing();
        ClearBackground(darkBlue);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
