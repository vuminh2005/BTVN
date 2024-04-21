#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "game.h"

using namespace std;

const int SCREEN_HEIGHT = 620;
const int SCREEN_WIDTH = 900;
const char* WINDOW_TITLE = "Tetris with SDL2";

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Game game = Game(renderer);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            game.HandleInput(event);
        }

        while (game.tutorial) {
            game.Tutorial(renderer);
            while (SDL_PollEvent(&event) != 0) {
                game.HandleInput(event);
            }
        }

        if (EventTriggered(1150 - game.level * 100)) {
            game.MoveBlockDown();
            game.UpdateScore(0, 1);
        }

        game.Draw(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    game.Clean();

    return 0;
}
