#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <deque>
#include <functional>

class Game{
    public:
        Game();
        //defult
        float gravity = 0.5f;
        float ARR = 0.05f; // Auto Repeat Rate
        float DAS = 0.15f; //Delayed Auto Shift
        int SDF = 6; //Soft Drop Factor

        void Draw();

        void HandleInput();
        void MoveBlockLeft();
        void MoveBlockRight();
        void MoveBlockDown();
        void Hold();

        bool GravityTriggered();
        Grid grid;
        double currentTime = GetTime();

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
        const float OrigGravity = gravity;
};
