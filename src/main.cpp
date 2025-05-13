    #include <raylib.h>
    #include "game.h"

    int main() {
        Color gray = {41,41,41,255};
        SetTargetFPS(60);
        InitWindow(720, 800, "Tetris"); //grid:400x800

        Game game = Game();


        //Config
        game.gravity = 1.f; //Drop cycle
        game.ARR = 0.033f; // Auto Repeat Rate
        game.DAS = 0.142f; //Delayed Auto Shift
        game.SDF = 6;//Soft Drop Factor

        // Game Loop
        while(!WindowShouldClose()){
            game.currentTime = GetTime();
            game.HandleInput();
            if(game.GravityTriggered()){
                game.MoveBlockDown();
            }

            BeginDrawing();
            ClearBackground(gray);

            game.Draw();

            EndDrawing();
        }

        CloseWindow();
    }