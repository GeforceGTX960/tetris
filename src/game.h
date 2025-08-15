#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "config.h"
#include <deque>
#include <functional>

class Game{
    public:
        Game();

        float gravity;
        float ARR ;
        float DAS;
        int SDF;

        void Draw();

        void HandleInput();
        void MoveBlockLeft();
        void MoveBlockRight();
        void MoveBlockDown();
        void Hold();

        bool GravityTriggered();
        Grid grid;
        double currentTime = GetTime();

        bool gameOver = false;

    private:
        bool BlockFits();
        bool IsBlockOutside(Block block);
        bool BlockFits(Block block);
        void RotateBlock();
        bool IsBlockOutside();
        void RotateBlockLeft();
        void RotateBlock180();
        void HardDrop();
        void LockBlock();
        void DrawQueue();
        void DrawInterface();
        void HandleHeldInput(int KEY, double lastPressTime, std::function<void()>);
        void GameReset();
        Block GetRandomBlock();
        Block GetGhostBlock();
        Block GhostBlock;
        Block currentBlock;
        std::vector<Block> blocks;
        std::deque<Block> GetRandomQue();
        std::deque<Block> currentQue;
        std::deque<Block> nextQue;
        std::deque<Block> previewQue;
        Block holdBlock;
        double leftKeyHeldTime;
        double rightKeyHeldTime;
        double landedtime = 0;
        bool HasLanded = false;
        bool Isholdempty = true;
        bool holdUsed = false;
        bool leftKeyHeld = false;
        bool rightKeyHeld = false;
        double OrigGravity;
};
