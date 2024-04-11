#include <bits/stdc++.h>
#include "game-screen.h"
#include "sdl.h"
#include "game-constants.h"

using namespace std;

struct Visibility {
    bool isVisible=false;   //Có đang được hiển thị trên màn hình hay không
    int showTime=-1;        //Thời gian hiển thị nếu đang hiển thị. Nếu <=0: hiển thị không thời hạn
    int waitTime=-1;        //Thời gian đợi để hiển thị nếu đang ẩn. Nếu <=0: ẩn không thời hạn
};

struct ScreenVisibility {
    Visibility vStartMsg, vHumanMsg, vHumanNumber;
    Visibility vComputerMsg, vComputerComparision, vJustClicked;
};

void loadNewGame(int &randomNumber, int markedNumbers[], int arrSize, ScreenVisibility &screen);
void renderGame(int number, int markedNumbers[], int elapsedTime, ScreenVisibility &screen);
int getUserInput();
void updateStates(int justClickedNumber, int randomNumber, int &number, int markedNumbers[], ScreenVisibility &screen);
bool isGameOver(int number, int randomNumber, const ScreenVisibility &screen);
int generateRandomNumber();
uint64_t timeSinceEpochMillisec();

int main()
{
    srand(time(0));
    load_SDL_And_Images();

    int randomNumber, number = 0, markedNumbers[MAX_NUM + 1];
    ScreenVisibility screen;
    loadNewGame(randomNumber, markedNumbers, MAX_NUM + 1, screen);

    uint64_t currentTime = timeSinceEpochMillisec();
    do {
        SDL_Delay(DELAY_TIME);

        uint64_t lastTime = currentTime;
        currentTime = timeSinceEpochMillisec();
        int elapsedTime = currentTime - lastTime;
        renderGame(number, markedNumbers, elapsedTime, screen);

        int justClickedNumber = getUserInput();

        updateStates(justClickedNumber, randomNumber, number, markedNumbers, screen);
    } while (!isGameOver(number, randomNumber, screen));

    waitUntilKeyPressed();
    unload_SDL_And_Images();

    return 0;
}

void loadNewGame(int &randomNumber, int markedNumbers[], int arrSize, ScreenVisibility &screen)
{
    randomNumber = generateRandomNumber();
    for (int i = 0; i < arrSize; i++) {
        markedNumbers[i] = INVALID_NUMBER;
    }

    screen.vStartMsg.isVisible = false;
    screen.vStartMsg.showTime = -1;
    screen.vStartMsg.waitTime = PAUSE_TIME - DELAY_TIME;
}

Visibility updateVisibility(Visibility v, int elapsedTime)
{
    if (v.isVisible) {
        if (v.showTime > 0) {
            v.showTime -= elapsedTime;
            if (v.showTime <= 0) v.isVisible = false;
        }
    } else {
        if (v.waitTime > 0) {
            v.waitTime -= elapsedTime;
            if (v.waitTime <= 0) v.isVisible = true;
        }
    }
    return v;
}

void renderGame(int number, int markedNumbers[], int elapsedTime, ScreenVisibility &screen)
{
    showBackground();

    screen.vJustClicked = updateVisibility(screen.vJustClicked, elapsedTime);
    if (screen.vJustClicked.isVisible) printClickedMarks(markedNumbers, number);
    else printClickedMarks(markedNumbers, -1);

    screen.vStartMsg = updateVisibility(screen.vStartMsg, elapsedTime);
    if (screen.vStartMsg.isVisible) printStartMsg();

    screen.vHumanMsg = updateVisibility(screen.vHumanMsg, elapsedTime);
    if (screen.vHumanMsg.isVisible) printHumanMsg();

    screen.vHumanNumber = updateVisibility(screen.vHumanNumber, elapsedTime);
    if (screen.vHumanNumber.isVisible) printHumanNumber(number);

    screen.vComputerMsg = updateVisibility(screen.vComputerMsg, elapsedTime);
    if (screen.vComputerMsg.isVisible) printComputerMsg();

    screen.vComputerComparision = updateVisibility(screen.vComputerComparision, elapsedTime);
    if (screen.vComputerComparision.isVisible) printComputerComparision(markedNumbers[number]);

    renderScreen();
}

int getUserInput()
{
    SDL_Event e;
    int number = INVALID_NUMBER;
    while (SDL_PollEvent(&e)) {
        if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            unload_SDL_And_Images;
            exit(1);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            number = calculateNumber(e.button.x, e.button.y);
            break;
        }
    }
    return number;
}

void updateStates(int justClickedNumber, int randomNumber, int &number, int markedNumbers[], ScreenVisibility &screen)
{
    if (justClickedNumber == INVALID_NUMBER) return;
    if (!screen.vComputerComparision.isVisible && !screen.vStartMsg.isVisible) return;

    number = justClickedNumber;
    if (number > randomNumber) {
        markedNumbers[number] = TOO_BIG;
    } else if (number < randomNumber) {
        markedNumbers[number] = TOO_SMALL;
    } else {
        markedNumbers[number] = THE_SAME;
    }

    screen.vStartMsg.isVisible = false;
    screen.vStartMsg.showTime = -1;
    screen.vStartMsg.waitTime = -1;

    screen.vJustClicked.isVisible = true;
    screen.vJustClicked.showTime = 3* PAUSE_TIME - DELAY_TIME;
    screen.vJustClicked.waitTime=-1;

    screen.vHumanMsg.isVisible = true;
    screen.vHumanMsg.showTime = PAUSE_TIME - DELAY_TIME;
    screen.vHumanMsg.waitTime =-1;

    screen.vHumanNumber.isVisible = false;
    screen.vHumanNumber.showTime = -1;
    screen.vHumanNumber.waitTime = screen.vHumanMsg.showTime + DELAY_TIME;

    screen.vComputerMsg.isVisible = false;
    screen.vComputerMsg.showTime = -1;
    screen.vComputerMsg.waitTime = screen.vHumanNumber.waitTime + PAUSE_TIME + DELAY_TIME;

    screen.vComputerComparision.isVisible = false;
    screen.vComputerComparision.showTime = -1;
    screen.vComputerComparision.waitTime = screen.vComputerMsg.waitTime + PAUSE_TIME + DELAY_TIME;
}

bool isGameOver(int number, int randomNumber, const ScreenVisibility &screen)
{
    return ((number == randomNumber) && screen.vComputerComparision.isVisible);
}

int generateRandomNumber()
{
    return rand % MAX_NUM + 1;
}

uint64_t timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
