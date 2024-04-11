#pragma once
#include <bits/stdc++.h>
#include "blocks.cpp"
#include "grid.h"

class Game {
public:
    Game();
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    Grid grid;

private:
    bool isBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};