#include "game.h"
#include "colors.h"

using namespace std;

Game::Game(SDL_Renderer* renderer)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    gameOver = false;
    notHold = true;
    sdl2Font.font = TTF_OpenFont("monogram.ttf", 50);
    sdl2Font.color = white;
    score = 0;
    InitInterface(renderer);
    grid = Grid();
    grid.linesCompleted = 0;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock1 = GetRandomBlock();
    nextBlock2 = GetRandomBlock();
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        keyProcessed[i] = false;
    }
    music = Mix_LoadMUS("good-night-160166.mp3");
    Mix_PlayMusic(music, -1);
}

void Game::InitInterface(SDL_Renderer* renderer)
{
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

    wjpu_rect.x = 50;
    wjpu_rect.y = 235;
    wjpu_rect.w = 200;
    wjpu_rect.h = 370;

    nextSurface = TTF_RenderText_Blended(sdl2Font.font, "NEXT", sdl2Font.color);
    nextTexture = SDL_CreateTextureFromSurface(renderer, nextSurface);
    nextRect = {715, 1, nextSurface->w, nextSurface->h};

    scoreSurface = TTF_RenderText_Blended(sdl2Font.font, "SCORE", sdl2Font.color);
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    scoreRect = {704, 380, scoreSurface->w, scoreSurface->h};

    levelSurface = TTF_RenderText_Blended(sdl2Font.font, "LEVEL", sdl2Font.color);
    levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
    levelRect = {705, 507, levelSurface->w, levelSurface->h};

    holdSurface = TTF_RenderText_Blended(sdl2Font.font, "HOLD", sdl2Font.color);
    holdTexture = SDL_CreateTextureFromSurface(renderer, holdSurface);
    holdRect = {115, 1, holdSurface->w, holdSurface->h};

    endSurface = TTF_RenderText_Blended(sdl2Font.font, "GAME OVER", sdl2Font.color);
    endTexture = SDL_CreateTextureFromSurface(renderer, endSurface);
    endRect = {365, 280, endSurface->w, endSurface->h};

    wjpuTexture = IMG_LoadTexture(renderer, "kawaii.jpg");
}

void Game::DisplayScore(SDL_Renderer* renderer)
{
    sprintf(scoreText, "%d", score);
    TTF_SizeText(sdl2Font.font, scoreText, &textWidth, &textHeight);
    pointSurface = TTF_RenderText_Blended(sdl2Font.font, scoreText, sdl2Font.color);
    pointTexture = SDL_CreateTextureFromSurface(renderer, pointSurface);
    pointRect = {667 + (170 - textWidth) / 2, 431, pointSurface->w, pointSurface->h};
    SDL_RenderCopy(renderer, pointTexture, NULL, &pointRect);
}

void Game::DisplayLevel(SDL_Renderer* renderer)
{
    TTF_SizeText(sdl2Font.font, speedText, &speedWidth, &speedHeight);
    speedSurface = TTF_RenderText_Blended(sdl2Font.font, speedText, sdl2Font.color);
    speedTexture = SDL_CreateTextureFromSurface(renderer, speedSurface);
    speedRect = {667 + (170 - speedWidth) / 2, 558, speedSurface->w, speedSurface->h};
    SDL_RenderCopy(renderer, speedTexture, NULL, &speedRect);
}

void Game::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 44, 44, 127, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 59, 85, 162, 255);
    SDL_RenderFillRect(renderer, &next_rect);
    SDL_RenderFillRect(renderer, &score_rect);
    SDL_RenderFillRect(renderer, &level_rect);
    SDL_RenderFillRect(renderer, &hold_rect);

    SDL_RenderCopy(renderer, nextTexture, NULL, &nextRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);
    SDL_RenderCopy(renderer, holdTexture, NULL, &holdRect);
    SDL_RenderCopy(renderer, wjpuTexture, NULL, &wjpu_rect);

    DisplayScore(renderer);

    if (level <= 10) level = grid.linesCompleted / 5 + 1;
    if (level != 11) sprintf(speedText, "%d", level);
    else sprintf(speedText, "%s", "MAX");
    DisplayLevel(renderer);

    grid.Draw(renderer);
    currentBlock.Draw(renderer, 300, 10);

    switch (nextBlock1.id) {
        case 3:
            nextBlock1.Draw(renderer, 602, 113);
            break;
        case 4:
            nextBlock1.Draw(renderer, 602, 96);
            break;
        default:
            nextBlock1.Draw(renderer, 615, 100);
            break;
    }

    switch (nextBlock2.id) {
        case 3:
        case 4:
            nextBlock2.Draw(renderer, 602, 240);
            break;
        default:
            nextBlock2.Draw(renderer, 615, 240);
            break;
    }

    if (notReset) {
        switch (holdBlock.id) {
            case 3:
                holdBlock.DisplayHoldBlock(renderer, 91, 83);
                break;
            case 4:
                holdBlock.DisplayHoldBlock(renderer, 121, 96);
                break;
            default:
                holdBlock.DisplayHoldBlock(renderer, 106, 96);
                break;
        }
    }

    if (gameOver) {
        SDL_SetRenderDrawColor(renderer, 59, 85, 162, 255);
        SDL_RenderFillRect(renderer, &end_rect);
        SDL_RenderCopy(renderer, endTexture, NULL, &endRect);
    }

    SDL_RenderPresent(renderer);
}

void Game::Tutorial(SDL_Renderer* renderer)
{
    SDL_Rect tutorial_rect;
    tutorial_rect.x = 200;
    tutorial_rect.y = 160;
    tutorial_rect.w = 500;
    tutorial_rect.h = 300;

    SDL_Surface* enterSurface = TTF_RenderText_Blended(sdl2Font.font, "ENTER", sdl2Font.color);
    SDL_Texture* enterTexture = SDL_CreateTextureFromSurface(renderer, enterSurface);
    SDL_Rect enterRect = {400, 415, enterSurface->w, enterSurface->h};

    SDL_Surface* moveSurface = TTF_RenderText_Blended(sdl2Font.font, "Move", sdl2Font.color);
    SDL_Texture* moveTexture = SDL_CreateTextureFromSurface(renderer, moveSurface);
    SDL_Rect moveRect = {220, 170, moveSurface->w, moveSurface->h};

    SDL_Surface* rotateSurface = TTF_RenderText_Blended(sdl2Font.font, "Rotate", sdl2Font.color);
    SDL_Texture* rotateTexture = SDL_CreateTextureFromSurface(renderer, rotateSurface);
    SDL_Rect rotateRect = {220, 215, rotateSurface->w, rotateSurface->h};

    SDL_Surface* dropSurface = TTF_RenderText_Blended(sdl2Font.font, "Drop", sdl2Font.color);
    SDL_Texture* dropTexture = SDL_CreateTextureFromSurface(renderer, dropSurface);
    SDL_Rect dropRect = {220, 260, dropSurface->w, dropSurface->h};

    SDL_Surface* switchSurface = TTF_RenderText_Blended(sdl2Font.font, "Hold", sdl2Font.color);
    SDL_Texture* switchTexture = SDL_CreateTextureFromSurface(renderer, switchSurface);
    SDL_Rect switchRect = {220, 305, switchSurface->w, switchSurface->h};

    SDL_Surface* resetSurface = TTF_RenderText_Blended(sdl2Font.font, "Replay", sdl2Font.color);
    SDL_Texture* resetTexture = SDL_CreateTextureFromSurface(renderer, resetSurface);
    SDL_Rect resetRect = {220, 350, resetSurface->w, resetSurface->h};

    SDL_Surface* arrowSurface = TTF_RenderText_Blended(sdl2Font.font, "Left/Down/Right", sdl2Font.color);
    SDL_Texture* arrowTexture = SDL_CreateTextureFromSurface(renderer, arrowSurface);
    SDL_Rect arrowRect = {390, 170, arrowSurface->w, arrowSurface->h};

    SDL_Surface* upSurface = TTF_RenderText_Blended(sdl2Font.font, "Up", sdl2Font.color);
    SDL_Texture* upTexture = SDL_CreateTextureFromSurface(renderer, upSurface);
    SDL_Rect upRect = {390, 215, upSurface->w, upSurface->h};

    SDL_Surface* spaceSurface = TTF_RenderText_Blended(sdl2Font.font, "Space", sdl2Font.color);
    SDL_Texture* spaceTexture = SDL_CreateTextureFromSurface(renderer, spaceSurface);
    SDL_Rect spaceRect = {390, 260, spaceSurface->w, spaceSurface->h};

    SDL_Surface* cSurface = TTF_RenderText_Blended(sdl2Font.font, "C", sdl2Font.color);
    SDL_Texture* cTexture = SDL_CreateTextureFromSurface(renderer, cSurface);
    SDL_Rect cRect = {390, 305, cSurface->w, cSurface->h};

    SDL_Surface* rSurface = TTF_RenderText_Blended(sdl2Font.font, "R (After G.Over)", sdl2Font.color);
    SDL_Texture* rTexture = SDL_CreateTextureFromSurface(renderer, rSurface);
    SDL_Rect rRect = {390, 350, rSurface->w, rSurface->h};

    SDL_SetRenderDrawColor(renderer, 44, 44, 127, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 59, 85, 162, 255);
    SDL_RenderFillRect(renderer, &tutorial_rect);
    SDL_RenderCopy(renderer, enterTexture, NULL, &enterRect);
    SDL_RenderCopy(renderer, moveTexture, NULL, &moveRect);
    SDL_RenderCopy(renderer, rotateTexture, NULL, &rotateRect);
    SDL_RenderCopy(renderer, dropTexture, NULL, &dropRect);
    SDL_RenderCopy(renderer, switchTexture, NULL, &switchRect);
    SDL_RenderCopy(renderer, resetTexture, NULL, &resetRect);
    SDL_RenderCopy(renderer, arrowTexture, NULL, &arrowRect);
    SDL_RenderCopy(renderer, upTexture, NULL, &upRect);
    SDL_RenderCopy(renderer, spaceTexture, NULL, &spaceRect);
    SDL_RenderCopy(renderer, cTexture, NULL, &cRect);
    SDL_RenderCopy(renderer, rTexture, NULL, &rRect);

    SDL_RenderPresent(renderer);

    currentBlock.Move(0, -1);

    if (!tutorial) {
        SDL_FreeSurface(enterSurface);
        SDL_FreeSurface(moveSurface);
        SDL_FreeSurface(rotateSurface);
        SDL_FreeSurface(dropSurface);
        SDL_FreeSurface(switchSurface);
        SDL_FreeSurface(resetSurface);
        SDL_FreeSurface(arrowSurface);
        SDL_FreeSurface(upSurface);
        SDL_FreeSurface(spaceSurface);
        SDL_FreeSurface(cSurface);
        SDL_FreeSurface(rSurface);

        SDL_DestroyTexture(enterTexture);
        SDL_DestroyTexture(moveTexture);
        SDL_DestroyTexture(rotateTexture);
        SDL_DestroyTexture(dropTexture);
        SDL_DestroyTexture(switchTexture);
        SDL_DestroyTexture(resetTexture);
        SDL_DestroyTexture(arrowTexture);
        SDL_DestroyTexture(upTexture);
        SDL_DestroyTexture(spaceTexture);
        SDL_DestroyTexture(cTexture);
        SDL_DestroyTexture(rTexture);
    }
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
                    UpdateScore(0, 1);
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
                            UpdateScore(0, 1);
                            if (IsBlockOutside() || BlockFits() == false) {
                                currentBlock.Move(-1,0);
                                UpdateScore(0, -1);
                                LockBlock();
                                check = false;
                            }
                        }
                    }
                    keyProcessed[SDL_SCANCODE_SPACE] = true;
                }
                break;
            case SDL_SCANCODE_C:
                if (!keyProcessed[SDL_SCANCODE_C]) {
                    HoldBlock();
                    keyProcessed[SDL_SCANCODE_C] = true;
                }
                break;
            case SDL_SCANCODE_RETURN:
                if (!keyProcessed[SDL_SCANCODE_RETURN]) {
                    tutorial = false;
                    keyProcessed[SDL_SCANCODE_RETURN] = true;
                }
                break;
            default:
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        keyProcessed[event.key.keysym.scancode] = false;
    }
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
    currentBlock = nextBlock1;
    nextBlock1 = nextBlock2;
    if (BlockFits() == false) {
        gameOver = true;
    }
    nextBlock2 = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
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
    nextBlock1 = GetRandomBlock();
    nextBlock2 = GetRandomBlock();
    grid.Initialize();
    score = 0;
    level = 0;
    grid.linesCompleted = 0;
    notHold = true;
    notReset = false;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    if (!gameOver) {
        switch (linesCleared) {
            case 1:
                score += 100;
                break;
            case 2:
                score += 300;
                break;
            case 3:
                score += 500;
                break;
            case 4:
                score += 1000;
                break;
            default:
                break;
            }
        score += moveDownPoints;
    }
}

void Game::HoldBlock()
{
    notReset = true;
    if (!notHold) {
        temp = holdBlock;
        holdBlock = currentBlock;
        currentBlock = temp;
    } else {
        holdBlock = currentBlock;
        currentBlock = nextBlock1;
        nextBlock1 = nextBlock2;
        nextBlock2 = GetRandomBlock();
        notHold = false;
    }
}

void Game::Clean()
{
    SDL_FreeSurface(nextSurface);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(levelSurface);
    SDL_FreeSurface(holdSurface);
    SDL_FreeSurface(endSurface);
    SDL_FreeSurface(pointSurface);
    SDL_FreeSurface(speedSurface);

    SDL_DestroyTexture(nextTexture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(levelTexture);
    SDL_DestroyTexture(holdTexture);
    SDL_DestroyTexture(endTexture);
    SDL_DestroyTexture(pointTexture);
    SDL_DestroyTexture(speedTexture);
    SDL_DestroyTexture(wjpuTexture);

    TTF_CloseFont(sdl2Font.font);
    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
