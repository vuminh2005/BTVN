#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <SDL_ttf.h>

using namespace std;

typedef struct {
    TTF_Font* font;
    SDL_Color color;
} SDL2_Font;

class Game
{
public:
    Game(SDL_Renderer* renderer);
    Grid grid;
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void Draw(SDL_Renderer* renderer);
    void HandleInput(SDL_Event event);
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    bool gameOver;
    void InitInterface(SDL_Renderer* renderer);

    SDL_Surface* nextSurface;
    SDL_Surface* scoreSurface;
    SDL_Surface* levelSurface;
    SDL_Surface* holdSurface;
    SDL_Surface* endSurface;

    SDL_Texture* nextTexture;
    SDL_Texture* scoreTexture;
    SDL_Texture* levelTexture;
    SDL_Texture* holdTexture;
    SDL_Texture* endTexture;

    SDL_Rect next_rect;
    SDL_Rect score_rect;
    SDL_Rect level_rect;
    SDL_Rect hold_rect;
    SDL_Rect end_rect;

    SDL_Rect nextRect;
    SDL_Rect scoreRect;
    SDL_Rect levelRect;
    SDL_Rect holdRect;
    SDL_Rect endRect;
private:
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool keyProcessed[SDL_NUM_SCANCODES];
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
};
