#include <bits/stdc++.h>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;
const char* WINDOW_TITLE = "Hello World!";

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void drawHangman(SDL_Window* window, SDL_Renderer* renderer, int attempt)
{
    int centerX = 550;
    int centerY = 350;
    int radius = 50;

    SDL_Rect bot, mid, top;
    bot.x = 100;
    bot.y = 650;
    bot.w = 200;
    bot.h = 50;
    mid.x = 175;
    mid.y = 150;
    mid.w = 50;
    mid.h = 500;
    top.x = 175;
    top.y = 100;
    top.w = 400;
    top.h = 50;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bot);
    SDL_RenderFillRect(renderer, &mid);
    SDL_RenderFillRect(renderer, &top);

    switch (attempt) {
        case 7:
            SDL_RenderDrawLine(renderer, 550, 500, 600, 600);
        case 6:
            SDL_RenderDrawLine(renderer, 550, 500, 500, 600);
        case 5:
            SDL_RenderDrawLine(renderer, 550, 425, 625, 450);
        case 4:
            SDL_RenderDrawLine(renderer, 550, 425, 475, 450);
        case 3:
            SDL_RenderDrawLine(renderer, 550, 400, 550, 500);
        case 2:
            for (int y = -radius; y <= radius; y++) {
                for (int x = -radius; x <= radius; x++) {
                    if (x * x + y * y <= radius * radius) {
                        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
                    }
                }
            }
        case 1:
            SDL_RenderDrawLine(renderer, 550, 150, 550, 300);
            break;
    }
}

//    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
//    SDL_Renderer* renderer = createRenderer(window);
//
//    SDL_RenderClear(renderer);

//    drawHangman(window, renderer, attempt);

//    SDL_RenderPresent(renderer);

//    waitUntilKeyPressed();
//    quitSDL(window, renderer);

int main(int argc, char* argv[])
{
//    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
//    SDL_Renderer* renderer = createRenderer(window);

    int attempt = 0;
    string secretWord = "hangman";
    string guessWord = "_______";


    while (attempt < 7 && guessWord != secretWord) {
//        SDL_RenderClear(renderer);
//
//        drawHangman(window, renderer, attempt);
//
//        SDL_RenderPresent(renderer);

        int counts = 0;
        cout << guessWord << endl;
        cout << "Guess a character (" << 7 - attempt << " chance(s) left):";

        char guess;
        cin >> guess;

        for (int i = 0; i < secretWord.size(); i++) {
            if (guess == secretWord[i]) {
                guessWord[i] = guess;
                counts++;
            }
        }

        if (guessWord == secretWord) {
            cout << "Congratulations! You win!!!" << endl
                << "The word is: " << secretWord;
            return 1;
        }
        if (counts) continue;
        else attempt++;
        if (attempt == 7) {
            cout << "You lose!!! Better luck next time!" << endl
                << "The word is: " << secretWord;
            return -1;
        }
    }

//    waitUntilKeyPressed();
//    quitSDL(window, renderer);

    return 0;
}
