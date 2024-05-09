#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include "grid.h"

using namespace std;

class Block
{
public:
    Block();
    void Draw(SDL_Renderer* renderer, int offsetX, int offsetY);
    void DrawGhost(SDL_Renderer* renderer, int offsetX, int offsetY, Grid& grid);
    void DisplayHoldBlock(SDL_Renderer* renderer, int offsetX, int offsetY);
    void Move(int rows, int columns);
    vector<Position> GetCellPositions();
    vector<Position> GetGhostCellPositions(Grid& grid);
    void Rotate();
    void UndoRotation();
    int id;
    int rowOffset;
    int columnOffset;
    map<int, vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    vector<SDL_Color> colors;
};
