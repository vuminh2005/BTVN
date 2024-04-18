#include "game.h"
#include "colors.h"

using namespace std;

Game::Game(SDL_Renderer* renderer)
{
    InitInterface(renderer);
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        keyProcessed[i] = false;
    }
    gameOver = false;
}

void Game::InitInterface(SDL_Renderer* renderer)
{
    SDL2_Font sdl2Font;
    sdl2Font.font = TTF_OpenFont("monogram.ttf", 50);
    sdl2Font.color = white;

    next_rect.x = 650;
    next_rect.y = 50;
    next_rect.w = 200;
    next_rect.h = 300;

    score_rect.x = 650;
    score_rect.y = 430;
    score_rect.w = 200;
    score_rect.h = 50;

    level_rect.x = 650;
    level_rect.y = 555;
    level_rect.w = 200;
    level_rect.h = 50;

    hold_rect.x = 50;
    hold_rect.y = 50;
    hold_rect.w = 200;
    hold_rect.h = 150;

    end_rect.x = 350;
    end_rect.y = 277;
    end_rect.w = 199;
    end_rect.h = 50;

    nextSurface = TTF_RenderText_Blended(sdl2Font.font, "NEXT", sdl2Font.color);
    nextTexture = SDL_CreateTextureFromSurface(renderer, nextSurface);
    nextRect = {715, 1, nextSurface->w, nextSurface->h};

    scoreSurface = TTF_RenderText_Blended(sdl2Font.font, "SCORE", sdl2Font.color);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    scoreRect = {705, 380, scoreSurface->w, scoreSurface->h};

    levelSurface = TTF_RenderText_Blended(sdl2Font.font, "LEVEL", sdl2Font.color);
    levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
    levelRect = {705, 507, levelSurface->w, levelSurface->h};

    holdSurface = TTF_RenderText_Blended(sdl2Font.font, "HOLD", sdl2Font.color);
    holdTexture = SDL_CreateTextureFromSurface(renderer, holdSurface);
    holdRect = {115, 1, holdSurface->w, holdSurface->h};

    endSurface = TTF_RenderText_Blended(sdl2Font.font, "GAME OVER", sdl2Font.color);
    endTexture = SDL_CreateTextureFromSurface(renderer, endSurface);
    endRect = {365, 280, endSurface->w, endSurface->h};
}

Block Game::GetRandomBlock()
{
    if(blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 44, 44, 127, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, nextTexture, NULL, &nextRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);
    SDL_RenderCopy(renderer, holdTexture, NULL, &holdRect);

    SDL_SetRenderDrawColor(renderer, 59, 85, 162, 255);
    SDL_RenderFillRect(renderer, &next_rect);
    SDL_RenderFillRect(renderer, &score_rect);
    SDL_RenderFillRect(renderer, &level_rect);
    SDL_RenderFillRect(renderer, &hold_rect);

    grid.Draw(renderer);
    currentBlock.Draw(renderer);

    if (gameOver) {
        SDL_SetRenderDrawColor(renderer, 59, 85, 162, 255);
        SDL_RenderFillRect(renderer, &end_rect);
        SDL_RenderCopy(renderer, endTexture, NULL, &endRect);
    }

    SDL_RenderPresent(renderer);
}

void Game::HandleInput(SDL_Event event)
{
    if (gameOver) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_R) {
            gameOver = false;
            Reset();
        }
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_LEFT:
                if (!keyProcessed[SDL_SCANCODE_LEFT]) {
                    MoveBlockLeft();
                    keyProcessed[SDL_SCANCODE_LEFT] = true;
                }
                break;
            case SDL_SCANCODE_RIGHT:
                if (!keyProcessed[SDL_SCANCODE_RIGHT]) {
                    MoveBlockRight();
                    keyProcessed[SDL_SCANCODE_RIGHT] = true;
                }
                break;
            case SDL_SCANCODE_DOWN:
                if (!keyProcessed[SDL_SCANCODE_DOWN]) {
                    MoveBlockDown();
                    keyProcessed[SDL_SCANCODE_DOWN] = true;
                }
                break;
            case SDL_SCANCODE_UP:
                if (!keyProcessed[SDL_SCANCODE_UP]) {
                    RotateBlock();
                    keyProcessed[SDL_SCANCODE_UP] = true;
                }
                break;
            case SDL_SCANCODE_SPACE:
                if (!keyProcessed[SDL_SCANCODE_SPACE]) {
                    bool check = true;
                    while (check) {
                        if (!gameOver) {
                            currentBlock.Move(1,0);
                            if (IsBlockOutside() || BlockFits() == false) {
                                currentBlock.Move(-1,0);
                                LockBlock();
                                check = false;
                            }
                        }
                    }
                    keyProcessed[SDL_SCANCODE_SPACE] = true;
                }
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        keyProcessed[event.key.keysym.scancode] = false;
    }
}

void Game::MoveBlockLeft() {
    if (!gameOver) {
        currentBlock.Move(0,-1);
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight() {
    if (!gameOver) {
        currentBlock.Move(0,1);
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(0,-1);
        }
    }
}

void Game::MoveBlockDown() {
    if (!gameOver) {
        currentBlock.Move(1,0);
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver) {
        currentBlock.Rotate();
        if (IsBlockOutside()) {
            currentBlock.UndoRotation();
        }
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false) {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    grid.ClearFullRows();
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.IsCellEmpty(item.row, item.column) == false) {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    grid.Initialize();
}
