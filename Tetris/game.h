#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

using namespace std;

typedef struct {
    TTF_Font* font;
    SDL_Color color;
} SDL2_Font;

class Game
{
public:
    Game(SDL_Renderer* renderer);
    void Draw(SDL_Renderer* renderer);
    void HandleInput(SDL_Event event);
    void MoveBlockDown();
    bool gameOver;
    void InitInterface(SDL_Renderer* renderer);
    int score;
    char scoreText[10];
    int textWidth, textHeight;
    void UpdateScore(int linesCleared, int moveDownPoints);
    void DisplayScore(SDL_Renderer* renderer);
    int level;
    char speedText[3];
    int speedWidth, speedHeight;
    void DisplayLevel(SDL_Renderer* renderer);
    void Tutorial(SDL_Renderer* renderer);
    bool tutorial = true;
    void Clean();

    Mix_Music *music;
    SDL2_Font sdl2Font;

    SDL_Surface* nextSurface;
    SDL_Surface* scoreSurface;
    SDL_Surface* levelSurface;
    SDL_Surface* holdSurface;
    SDL_Surface* endSurface;
    SDL_Surface* pointSurface;
    SDL_Surface* speedSurface;

    SDL_Texture* nextTexture;
    SDL_Texture* scoreTexture;
    SDL_Texture* levelTexture;
    SDL_Texture* holdTexture;
    SDL_Texture* endTexture;
    SDL_Texture* pointTexture;
    SDL_Texture* speedTexture;
    SDL_Texture* wjpuTexture;

    SDL_Rect next_rect;
    SDL_Rect score_rect;
    SDL_Rect level_rect;
    SDL_Rect hold_rect;
    SDL_Rect end_rect;
    SDL_Rect wjpu_rect;

    SDL_Rect nextRect;
    SDL_Rect scoreRect;
    SDL_Rect levelRect;
    SDL_Rect holdRect;
    SDL_Rect endRect;
    SDL_Rect pointRect;
    SDL_Rect speedRect;
private:
    Grid grid;
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock1;
    Block nextBlock2;
    Block holdBlock;
    Block temp;
    bool keyProcessed[SDL_NUM_SCANCODES];
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    void HoldBlock();
    bool BlockFits();
    void Reset();
    bool notHold;
    bool notReset;
};
