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
    void DisplayTutorial(SDL_Renderer* renderer);
    void CleanTutorial();
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
    SDL_Texture* logoTexture;

    SDL_Rect next_rect;
    SDL_Rect score_rect;
    SDL_Rect level_rect;
    SDL_Rect hold_rect;
    SDL_Rect end_rect;
    SDL_Rect logo_rect;

    SDL_Rect nextRect;
    SDL_Rect scoreRect;
    SDL_Rect levelRect;
    SDL_Rect holdRect;
    SDL_Rect endRect;
    SDL_Rect pointRect;
    SDL_Rect speedRect;

    SDL_Rect tutorial_rect;

    SDL_Surface* enterSurface;
    SDL_Texture* enterTexture;
    SDL_Rect enterRect;

    SDL_Surface* moveSurface;
    SDL_Texture* moveTexture;
    SDL_Rect moveRect;

    SDL_Surface* rotateSurface;
    SDL_Texture* rotateTexture;
    SDL_Rect rotateRect;

    SDL_Surface* dropSurface;
    SDL_Texture* dropTexture;
    SDL_Rect dropRect;

    SDL_Surface* switchSurface;
    SDL_Texture* switchTexture;
    SDL_Rect switchRect;

    SDL_Surface* resetSurface;
    SDL_Texture* resetTexture;
    SDL_Rect resetRect;

    SDL_Surface* arrowSurface;
    SDL_Texture* arrowTexture;
    SDL_Rect arrowRect;

    SDL_Surface* upSurface;
    SDL_Texture* upTexture;
    SDL_Rect upRect;

    SDL_Surface* spaceSurface;
    SDL_Texture* spaceTexture;
    SDL_Rect spaceRect;

    SDL_Surface* cSurface;
    SDL_Texture* cTexture;
    SDL_Rect cRect;

    SDL_Surface* rSurface;
    SDL_Texture* rTexture;
    SDL_Rect rRect;
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
