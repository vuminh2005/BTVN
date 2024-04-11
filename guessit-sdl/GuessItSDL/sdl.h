#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>

using namespace std;

void logSDLError(ostream& os, const string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture(const string &file, SDL_Renderer* ren);

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y);

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h);

#endif // SDL_H_INCLUDED
