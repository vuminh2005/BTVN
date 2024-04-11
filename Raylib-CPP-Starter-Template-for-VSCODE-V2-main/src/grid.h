#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Grid {
public:
    Grid();
    void Init();
    void Print();
    void Draw();
    bool isCellOutside(int row, int col);
    bool isCellEmpty(int row, int col);
    int grid[20][10];
private:
    int numRows, numCols, cellSize;
    vector<Color> colors;
};