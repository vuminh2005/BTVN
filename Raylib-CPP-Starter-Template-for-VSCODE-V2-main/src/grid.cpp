#include <bits/stdc++.h>
#include "grid.h"
#include "colors.h"

using namespace std;

Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 40;
    colors = GetCellColors();
}

void Grid::Init() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

void Grid::Draw() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 200, row * cellSize + 200, cellSize, cellSize, colors[cellValue]);
        }
    }
}

bool Grid::isCellOutside(int row, int col) {
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) return false;
    return true;
}

bool Grid::isCellEmpty(int row, int col) {
    if (grid[row][col] == 0) return true;
    return false;
}
