#pragma once
#include <vector>
#include <raylib.h>

class Grid{
    public:
        Grid();
        void Initialize();
        void print();
        void Draw();
        int ClearFullRows();
        bool IsCellOutside(int row, int column);
        bool IsCellEmpty(int row, int column);
        int grid[20][10];
    private:
        bool IsRowFull(int row);
        void ClearRow(int row);
        void MoveRowDown(int row, int numRows);
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
};