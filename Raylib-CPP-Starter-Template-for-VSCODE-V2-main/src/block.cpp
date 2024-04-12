#include "block.h"
#include <bits/stdc++.h>

using namespace std;

Block::Block() {
    cellSize = 40;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

void Block::Draw() {
    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles) {
        DrawRectangle(item.col * cellSize + 200, item.row * cellSize + 200, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols) {
    rowOffset += rows;
    colOffset += cols;
}

vector<Position> Block::GetCellPositions() {
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles) {
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate() {
    rotationState++;
    if (rotationState == (int)cells.size()) rotationState = 0;
}

void Block::UndoRotation() {
    rotationState--;
    if (rotationState == -1) rotationState = cells.size() - 1;
}