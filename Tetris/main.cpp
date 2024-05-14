#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "game.h"
#include <chrono>
#include <iostream>

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

    while (game.tutorial) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                game.tutorial = false;
            }
            game.HandleInput(event);
        }
        game.DisplayTutorial(renderer);
        if (!game.tutorial) game.CleanTutorial();
    }

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            game.HandleInput(event);
        }

        game.Draw(renderer);

        if (EventTriggered(1050 - game.level * 100)) {
            game.MoveBlockDown();
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    game.Clean();

    return 0;
}

// sound
// line cleared effect
