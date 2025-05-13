#include "block.h"

Block::Block(){
    cellSize = 40;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
    Move(0, 3);
}

void Block::DrawFade(){
    std::vector<Position> tiles = GetCellPositions();
    for(Position item: tiles){
        DrawRectangle(item.column * cellSize + 161, item.row * cellSize + 1, cellSize - 1, cellSize - 1, Fade(colors[id], 0.25f));
    }
}

void Block::Draw(){
    std::vector<Position> tiles = GetCellPositions();
    for(Position item: tiles){
        DrawRectangle(item.column * cellSize + 161, item.row * cellSize + 1, cellSize - 1, cellSize - 1, colors[id]);
    }
}


void Block::Move(int rows, int columns){
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions(){
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item: tiles){
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate(){
    rotationState ++;
    rotationState %=4;
}

void Block::RotateLeft(){
    rotationState --;
    if(rotationState < 0){
        rotationState = cells.size() -1;
    }
}

void Block::RotateBlock180(){
    rotationState +=2;
    rotationState %=4;
}

void Block::Reset(){
    rotationState = 0;
    rowOffset = 0;
    columnOffset = 3;
}
