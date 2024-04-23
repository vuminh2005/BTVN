#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

using namespace std;

class Block
{
public:
    Block();
    void Draw(SDL_Renderer* renderer, int offsetX, int offsetY);
    void DisplayHoldBlock(SDL_Renderer* renderer, int offsetX, int offsetY);
    void Move(int rows, int columns);
    vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    map<int, vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    vector<SDL_Color> colors;
    int rowOffset;
    int columnOffset;
};
