#ifndef GAME-SCREEN_H_INCLUDED
#define GAME-SCREEN_H_INCLUDED

void load_SDL_And_Images();
void unload_SDL_And_Images();

void renderScreen();
void showBackground();
void printStartMsg();
void printHumanMsg();
void printHumanNumber(int number);
void printComputerMsg();
void printComputerComparision(int comparision);
void printClickedMarks(int markedNumbers[], int clicked_number);

int calculateNumber(int x, int y);

#endif // GAME-SCREEN_H_INCLUDED
