#pragma once
#include <vector>
#include <SDL.h>

using namespace std;

class Grid
{
public:
    Grid();
    void Initialize();
    int grid[20][10];
    void Print();
    void Draw(SDL_Renderer* renderer);
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int linesCompleted;
private:
    int numRows;
    int numCols;
    int cellSize;
    vector<SDL_Color> colors;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int rowCount);
};
