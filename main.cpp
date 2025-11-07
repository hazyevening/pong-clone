#include <iostream>
#include "raylib.h"
#include <string> 

int main() {

    std::string screen {"TITLE"};

    int framesCounter {};
    
    constexpr int screenWidth {1920};
    constexpr int screenHeight {1080};

    std::cout << framesCounter;
    
    InitWindow(screenWidth, screenHeight, "raylib test");
    SetTargetFPS(60);    

    while (!WindowShouldClose()) {
        //UPDATE    
        if (screen == "TITLE") {
            ++framesCounter;
            if (framesCounter > 100) {
                screen = "GAME";     
                framesCounter = 0;           
            }
        }
        else if (screen == "GAME") {
            ++framesCounter;
            if (IsKeyPressed(KEY_SPACE)) {
                screen = "ENDING";
            }
        }
        else if (screen == "ENDING") {
            if (IsKeyPressed(KEY_SPACE)) {
                screen = "TITLE";
            }
        }
        

        //DRAW 
        BeginDrawing();
        if (screen == "TITLE") {
            ClearBackground(BLUE);
            DrawText("This is the Title Screen", (screenWidth / 2 - MeasureText("This is the Title Screen", 80) / 2), 75, 80, BLACK);
        }
        else if (screen == "GAME") {
            ClearBackground(ORANGE);
            DrawText("This is the Gameplay Screen", (screenWidth / 2 - MeasureText("This is the Gameplay Screen", 80) / 2), 75, 80, BLACK);
        }        
        else if (screen == "ENDING") {
            ClearBackground(GREEN);
            DrawText("This is the Ending Screen", (screenWidth / 2 - MeasureText("This is the Ending Screen", 80) / 2), 75, 80, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;        
}
