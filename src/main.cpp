    #include <raylib.h>
    #include "game.h"

    int main() {
        Color gray = {41,41,41,255};
        SetTargetFPS(60);
        int WindowWidth = 720;
        int WindowLength = 800;
        InitWindow(WindowWidth, WindowLength, "Tetris"); //grid:400x800

        Game game = Game();


        //Config
        game.gravity = 0.5f; //Drop cycle
        game.ARR = 0.05f; // Auto Repeat Rate
        game.DAS = 0.15f; //Delayed Auto Shift
        game.SDF = -1;//Soft Drop Factor

        // Game Loop
        while(!WindowShouldClose()){
            game.currentTime = GetTime();
            game.HandleInput();
            if(game.GravityTriggered() && !game.gameOver){
                game.MoveBlockDown();
            }

            BeginDrawing();
            ClearBackground(gray);

            game.Draw();

            if(game.gameOver) {
                DrawRectangle(0, 0, 720, 800, Fade(RED, 0.3));
                DrawText("Game Over", 230, 250, 50, WHITE);
                DrawText("Press R To Restart", 235, 320, 25, WHITE);
            }

            EndDrawing();
        }

        CloseWindow();
    }