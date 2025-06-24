#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "color.h"



class Block{
    public:
        Block();
        void DrawFade();
        void Draw();
        void Move(int rows, int columns);
        std::vector<Position> GetCellPositions();
        void Rotate();
        void RotateLeft();
        void RotateBlock180();
        void Reset();
        int id;
        std::map<int, std::vector<Position>> cells;
        std::vector<Color> colors;
        void InitJLZSTkickTable();
        void InitIkickTable();
        int rotationState;
        std::map<std::pair<int, int>, std::vector<Position>> kickTable;
    private:
        int rowOffset;
        int columnOffset;
        int cellSize;
};