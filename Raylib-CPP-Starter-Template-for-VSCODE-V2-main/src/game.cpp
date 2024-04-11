#include "game.h"
#include <bits/stdc++.h>
#include <Windows.h>

using namespace std;

Game::Game() {
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
    if(blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() {
    grid.Init();
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    switch(keyPressed) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            break;
        case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft() {
    currentBlock.Move(0,-1);
    if (isBlockOutside() || BlockFits() == false) {
        currentBlock.Move(0,1);
    }
}

void Game::MoveBlockRight() {
    currentBlock.Move(0,1);
    if (isBlockOutside() || BlockFits() == false) {
        currentBlock.Move(0,-1);
    }
}

void Game::MoveBlockDown() {
    currentBlock.Move(1,0);
    if (isBlockOutside() || BlockFits() == false) {
        currentBlock.Move(-1,0);
        LockBlock();
    }
}

bool Game::isBlockOutside() {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.isCellOutside(item.row, item.col)) return true;
    }
    return false;
}

void Game::RotateBlock() {
    currentBlock.Rotate();
    if (isBlockOutside() || BlockFits() == false) currentBlock.UndoRotation();
}

void Game::LockBlock() {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
}

bool Game::BlockFits() {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.isCellEmpty(item.row, item.col) == false) {
            return false;
        }
    }
    return true;
}
