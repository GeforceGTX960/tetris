#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = {ZBlock(), LBlock(), OBlock(), SBlock(), IBlock(), JBlock(), TBlock()};
    currentQue = GetRandomQue();
    nextQue = GetRandomQue();
    currentBlock = GetRandomBlock();
    GhostBlock = GetGhostBlock();
}

std::deque<Block> Game::GetRandomQue(){
    std::deque<Block>dq;
    bool used[7] = {false};
    while(dq.size() <7){
        int randomIndex = rand() % 7;
        if(!used[randomIndex]){
            dq.push_back(blocks[randomIndex]);
            used[randomIndex] = true;
        }
    }
    
    return dq;  
}

Block Game::GetRandomBlock(){
    if(currentQue.empty()){
        currentQue = nextQue;
        nextQue = GetRandomQue();
    }
    Block block;
    block = currentQue.front();
    currentQue.pop_front();

    return block;
}

void Game::Draw(){
    grid.Draw(); 
    currentBlock.Draw();
    GhostBlock.DrawFade();
    GhostBlock = GetGhostBlock();
    DrawQueue();
}

void Game::HandleInput(){
    //Press
    if (IsKeyPressed(KEY_X)) RotateBlock();
    if (IsKeyPressed(KEY_Z)) RotateBlockLeft();
    if (IsKeyPressed(KEY_A)) RotateBlock180();
    if (IsKeyPressed(KEY_C)) Hold();
    if (IsKeyPressed(KEY_SPACE)) HardDrop();
    
    if (IsKeyPressed(KEY_LEFT)){
        MoveBlockLeft();
        leftKeyHeld = true;
        leftKeyHeldTime = currentTime;
    }

    if (IsKeyPressed(KEY_RIGHT)){
        MoveBlockRight();
        rightKeyHeld = true;
        rightKeyHeldTime = currentTime;
    }

    if (IsKeyPressed(KEY_DOWN)){
        if(SDF == -1){
            while(!IsBlockOutside() && BlockFits()){
                currentBlock.Move(1,0);
            }
            currentBlock.Move(-1, 0);
        }else{
            gravity /= SDF;
        }
    }

    //Release
    if(IsKeyReleased(KEY_LEFT)) leftKeyHeld = false;
    if(IsKeyReleased(KEY_RIGHT)) rightKeyHeld = false;
    if(IsKeyReleased(KEY_DOWN)) gravity = OrigGravity;

    //Auto
    if(leftKeyHeld) HandleHeldInput(KEY_LEFT, leftKeyHeldTime, [this](){ MoveBlockLeft(); });
    if(rightKeyHeld) HandleHeldInput(KEY_RIGHT, rightKeyHeldTime, [this](){ MoveBlockRight(); });
}

void Game::HandleHeldInput(int KEY, double lastPressTime, std::function<void()> fn){

    if(currentTime - lastPressTime >= DAS){
        static double lastRepeatTime = 0;

        if(currentTime - lastRepeatTime >= ARR){
            fn();
            lastRepeatTime = currentTime;
        }
    }
}

void Game::MoveBlockLeft(){
    currentBlock.Move(0, -1);
    if(IsBlockOutside() || !BlockFits()){
        currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight(){
    currentBlock.Move(0, 1);
    if(IsBlockOutside() || !BlockFits()){
        currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown(){
    currentBlock.Move(1, 0);

    if(IsBlockOutside() || !BlockFits()){
        currentBlock.Move(-1, 0);

        if(!HasLanded){
            landedtime = GetTime();
            HasLanded = true;
        }
        else if(GetTime() - landedtime >= 3 * gravity){
            LockBlock();
            HasLanded = false;
        }
    }
    else{
        HasLanded = false;
    }
}

void Game::Hold(){
    if(holdUsed){
        return;
    }

    if(Isholdempty){
        currentBlock.Reset();
        holdBlock = currentBlock;
        currentBlock = GetRandomBlock();
        Isholdempty = false;
        holdUsed = true;
    }
    else{
        currentBlock.Reset();
        std::swap(holdBlock, currentBlock);
        holdUsed = true;
    }
}

bool Game::GravityTriggered(){
    static double lastUpdateTime = 0;
    if(currentTime - lastUpdateTime >= gravity){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Game::HardDrop(){
    while(!IsBlockOutside() && BlockFits()){
        currentBlock.Move(1,0);
    }
    currentBlock.Move(-1, 0);
    LockBlock();
}

void Game::RotateBlock(){
    for(auto it : currentBlock.kickTable[{currentBlock.rotationState, (currentBlock.rotationState+1)%4}]){
        Block tryBlock = currentBlock;
        tryBlock.Rotate();
        tryBlock.Move(it.column, it.row);
        if(!IsBlockOutside(tryBlock) && BlockFits(tryBlock)){
            currentBlock = tryBlock;
            break;
        }
    }
}

void Game::RotateBlockLeft(){
    for(auto it : currentBlock.kickTable[{currentBlock.rotationState, (currentBlock.rotationState+3)%4}]){
        Block tryBlock = currentBlock;
        tryBlock.RotateLeft();
        tryBlock.Move(it.column, it.row);
        if(!IsBlockOutside(tryBlock) && BlockFits(tryBlock)){
            currentBlock = tryBlock;
            break;
        }
    }
}

void Game::RotateBlock180(){
    currentBlock.RotateBlock180();
    if(IsBlockOutside() || !BlockFits()){
        currentBlock.RotateBlock180();
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position& item: tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = GetRandomBlock();
    grid.ClearFullRows();
    holdUsed = false;
}

void Game::DrawQueue(){
    previewQue.clear();
    for(size_t i = 0 ; i < 5; i++){
        if(i < currentQue.size()){
            previewQue.push_back(currentQue[i]);
        }
        else{
            previewQue.push_back(nextQue[i - currentQue.size()]);
        }
    }

    for(int i = 0; i < 5; i++){
        Block preview = previewQue[i];
        std::vector<Position> tiles = preview.cells[0];
        for(Position item: tiles){
        DrawRectangle(item.column * 30 + 591, item.row * 30 + i *90 + 10, 29, 29, preview.colors[preview.id]);
        }
    }

    //drawHold

    std::vector<Position> tiles = holdBlock.cells[0];
        for(Position item: tiles){
        DrawRectangle(item.column * 30 + -5, item.row * 30 + 10, 29, 29, holdBlock.colors[holdBlock.id]);
        }
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position& item : tiles){
        if(grid.IsCellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(const Position& item: tiles){
        if(grid.IsCellEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}

bool Game::IsBlockOutside(Block block){
    std::vector<Position> tiles = block.GetCellPositions();
    for(const Position& item : tiles){
        if(grid.IsCellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

bool Game::BlockFits(Block block){
    std::vector<Position> tiles = block.GetCellPositions();
    for(const Position& item: tiles){
        if(grid.IsCellEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}

Block Game::GetGhostBlock(){
    Block ghost = currentBlock;
    while(!IsBlockOutside(ghost) &&  BlockFits(ghost)){
        ghost.Move(1, 0);
    }
    ghost.Move(-1, 0);
    return ghost;
}