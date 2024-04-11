#pragma once
#include <bits/stdc++.h>
#include "position.h"
#include "colors.h"

using namespace std;

class Block {
public:
    Block();
    void Draw();
    void Move(int rowOffset, int colOffset);
    vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    map<int, vector<Position>> cells;
private:
    int cellSize, rotationState;
    vector<Color> colors;
    int rowOffset, colOffset;
};