#include "grid.h"
#include <iostream>
#include "colors.h"

using namespace std;

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print()
{
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

void Grid::Draw(SDL_Renderer* renderer)
{
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];
            SDL_SetRenderDrawColor(renderer, colors[cellValue].r, colors[cellValue].g, colors[cellValue].b, colors[cellValue].a);
            SDL_Rect rectangle = {column * cellSize + 300, row * cellSize + 10, cellSize - 1, cellSize - 1};
            SDL_RenderFillRect(renderer, &rectangle);
        }
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0) return true;
    return false;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++) {
        if (grid[row][column] == 0) return false;
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++) {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int rowCount)
{
    for (int column = 0; column < numCols; column++) {
        grid[row + rowCount][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        } else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}
