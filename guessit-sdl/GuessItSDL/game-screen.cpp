#include <bits/stdc++.h>
#include "game-screen.h"
#include "sdl.h"
#include "game-constants.h"

using namespace std;

const char WINDOW_TITLE[] = "GuessIt in Gameloop";
const int SCREEN_WIDTH = 861, SCREEN_HEIGHT = 517;
const int TABLE_X0 = 29, TABLE_Y0 = 285, TABLE_X1  = 829, TABLE_Y1 = 493;
const int TABLE_ROW_NUM = 5, TABLE_COL_NUM = 20;

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture *gameImg, *startMsg, *computerMsg, *humanMsg;
SDL_Texture *bigMsg, *smallMsg, *sameMsg;
SDL_Texture *bigMark, *smallMark, *sameMark, *clickMark;
SDL_Texture *numMsg[MAX_NUM +1 ];

void load_SDL_And_Images()
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    gameImg = loadTexture("images/game.bmp", renderer);
    startMsg = loadTexture("images/start.bmp", renderer);
    computerMsg = loadTexture("images/computer.bmp", renderer);
    humanMsg = loadTexture("images/human.bmp", renderer);
    bigMsg = loadTexture("images/big.bmp", renderer);
    smallMsg = loadTexture("images/small.bmp", renderer);
    sameMsg = loadTexture("images/same.bmp", renderer);
    bigMark = loadTexture("images/bigmark.bmp", renderer);
    smallMark = loadTexture("images/smallmark.bmp", renderer);
    sameMark = loadTexture("images/samemark.bmp", renderer);
    clickMark = loadTexture("images/clickmark.bmp", renderer);

    bool is_load_num_failed = false;

    for (int i = 1; i <= MAX_NUM; i++) {
        numMsg[i] = loadTexture("images/" + to_string(i) + ".bmp", renderer);
        if (numMsg[i] == nullptr) {
            is_load_num_failed = true;
            break;
        }
    }

    if (gameImg == nullptr  || startMsg == nullptr || computerMsg == nullptr
        || humanMsg == nullptr  || bigMsg == nullptr || smallMsg == nullptr
        || sameMsg == nullptr || is_load_num_failed){
        unload_SDL_And_Images();
        exit(1);
    }
}

void unload_SDL_And_Images()
{
    SDL_DestroyTexture(gameImg);
    SDL_DestroyTexture(startMsg);
    SDL_DestroyTexture(computerMsg);
    SDL_DestroyTexture(humanMsg);
    SDL_DestroyTexture(bigMsg);
    SDL_DestroyTexture(smallMsg);
    SDL_DestroyTexture(sameMsg);
    SDL_DestroyTexture(bigMark);
    SDL_DestroyTexture(smallMark);
    SDL_DestroyTexture(sameMark);
    SDL_DestroyTexture(clickMark);
    for (int i = 1; i <= MAX_NUM; i++) {
        SDL_DestroyTexture(numMsg[i]);
    }
    quitSDL(window, renderer);
}

void renderScreen()
{
    SDL_RenderPresent(renderer);
}

void showBackground()
{
    renderTexture(gameImg, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void printStartMsg()
{
    renderTexture(startMsg, renderer, 555, 132);
}

void printHumanMsg()
{
    renderTexture(humanMsg, renderer, 296, 107);
}

void printHumanNumber(int number)
{
    renderTexture(numMsg[number], renderer, 315, 102);
}

void printComputerMsg()
{
    renderTexture(computerMsg, renderer, 552, 130);
}

void printComputerComparision(int comparision)
{
    if (comparision == TOO_BIG) {
        renderTexture(bigMsg, renderer, 550, 147);
    } else if (comparision == TOO_SMALL) {
        renderTexture(smallMsg, renderer, 550, 147);
    } else {
        renderTexture(sameMsg, renderer, 550, 147);
    }
}

void get_X_y_Of_Number(int &x, int &y, int number)
{
    int cellWidth = (TABLE_X1 - TABLE_X0) / TABLE_COL_NUM, cellHeight = (TABLE_Y1 - TABLE_Y0) / TABLE_ROW_NUM;
    int row = (number - 1) / TABLE_COL_NUM, col = (number - 1) % TABLE_COL_NUM;
    x = TABLE_X0 + col * cellWidth + 2;
    y = TABLE_Y0 + row * cellHeight + 5;
}

void printClickedMarks(int markedNumbers[], int clicked_number = -1)
{
    for (int i = 1; i < MAX_NUM; i++) {
        int x, y;
        get_X_y_Of_Number(x, y, i);
        if (i == clicked_number) {
            renderTexture(clickMark, renderer, x, y);
        } else if (markedNumbers[i] == TOO_BIG) {
            renderTexture(bigMark, renderer, x, y);
        } else if (markedNumbers[i] == TOO_SMALL) {
            renderTexture(smallMark, renderer, x, y);
        } else {
            renderTexture(sameMark, renderer, x, y);
        }
    }
}

int calculateNumber(int x, int y)
{
    if (x < TABLE_X0 || x > TABLE_X1 || y < TABLE_Y0 || TABLE_Y1) return INVALID_NUMBER;
    int cellWidth = (TABLE_X1 - TABLE_X0) / TABLE_COL_NUM, cellHeight = (TABLE_Y1 - TABLE_Y0) / TABLE_ROW_NUM;
    int col = (x - TABLE_X0) / cellWidth, row = (y - TABLE_Y0) / cellHeight;
    return (row * TABLE_COL_NUM + col + 1);
}
