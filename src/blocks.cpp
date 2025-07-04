#include "block.h"
#include "position.h"

class ZBlock:public Block{
    public:
        ZBlock(){
            id = 1;
            cells[0] = {Position(0, 0), Position(0, 1), Position(1,1), Position(1, 2)};
            cells[1] = {Position(0, 2), Position(1, 1), Position(1,2), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(2,1), Position(2, 2)};
            cells[3] = {Position(0, 1), Position(1, 0), Position(1,1), Position(2, 0)};
            InitJLZSTkickTable();
        }
};
class LBlock:public Block{
    public:
        LBlock(){
            id = 2;
            cells[0] = {Position(0, 2), Position(1, 0), Position(1,1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(2,1), Position(2, 2)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1,2), Position(2, 0)};
            cells[3] = {Position(0, 0), Position(0, 1), Position(1,1), Position(2, 1)};
            InitJLZSTkickTable();
        }
};
class OBlock:public Block{
    public:
        OBlock(){
            id = 3;
            cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
            cells[1] = cells[0];
            cells[2] = cells[0];
            cells[3] = cells[0];
            Move(0, 1);
        }
    };
class SBlock:public Block{
    public:
        SBlock(){
            id = 4;
            cells[0] = {Position(0, 1), Position(0, 2), Position(1,0), Position(1, 1)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(1,2), Position(2, 2)};
            cells[2] = {Position(1, 1), Position(1, 2), Position(2,0), Position(2, 1)};
            cells[3] = {Position(0, 0), Position(1, 0), Position(1,1), Position(2, 1)};
            InitJLZSTkickTable();
        }
    };
class IBlock:public Block{
    public:
        IBlock(){
            id = 5;
            cells[0] = {Position(1, 0), Position(1, 1), Position(1,2), Position(1, 3)};
            cells[1] = {Position(0, 2), Position(1, 2), Position(2,2), Position(3, 2)};
            cells[2] = {Position(2, 0), Position(2, 1), Position(2,2), Position(2, 3)};
            cells[3] = {Position(0, 1), Position(1, 1), Position(2,1), Position(3, 1)};
            Move(-1, 0);
            InitIkickTable();
        }
};
class JBlock:public Block{
    public:
        JBlock(){
            id = 6;
            cells[0] = {Position(0, 0), Position(1, 0), Position(1,1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(0, 2), Position(1,1), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1,2), Position(2, 2)};
            cells[3] = {Position(0, 1), Position(1, 1), Position(2,0), Position(2, 1)};
            InitJLZSTkickTable();
        }
};

class TBlock:public Block{
    public:
        TBlock(){
            id = 7;
            cells[0] = {Position(0, 1), Position(1, 0), Position(1,1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(1,2), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1,2), Position(2, 1)};
            cells[3] = {Position(0, 1), Position(1, 0), Position(1,1), Position(2, 1)};
            InitJLZSTkickTable();
        }
};