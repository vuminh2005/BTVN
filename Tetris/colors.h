#pragma once
#include <vector>
#include <SDL.h>

using namespace std;

extern const SDL_Color darkGrey;
extern const SDL_Color green;
extern const SDL_Color red;
extern const SDL_Color orange;
extern const SDL_Color yellow;
extern const SDL_Color purple;
extern const SDL_Color cyan;
extern const SDL_Color blue;
extern const SDL_Color lightBlue;
extern const SDL_Color darkBlue;
extern const SDL_Color white;

vector<SDL_Color> GetCellColors();
