#include <iostream>
#include "raylib.h"
#include <string> 

int main() {

    std::string screen {"TITLE"};

    int framesCounter {};
    
    constexpr int screenWidth {1920};
    constexpr int screenHeight {1080};

    constexpr Color txtColor {WHITE};
    constexpr Color bgColor {BLACK};

    constexpr int playerHeight {100};
    constexpr int playerWidth {20};
    int playerPosY {((screenHeight / 2) - playerHeight)};
    constexpr int playerPosX {30};    
    constexpr int playerSpeed {10};    
    constexpr Color playerColor {WHITE};
    
    InitWindow(screenWidth, screenHeight, "raylib test");
    SetTargetFPS(60);    

    while (!WindowShouldClose()) {
        //UPDATE    
        if (screen == "TITLE") {
            ++framesCounter;
            // Change screen state
            if (IsKeyPressed(KEY_ENTER)) {
                screen = "GAME";
            }
        }
        else if (screen == "GAME") {
            ++framesCounter;
            // Detect player input
            if (IsKeyDown(KEY_DOWN)) {
                playerPosY += playerSpeed;
            }
            if (IsKeyDown(KEY_UP)) {
                playerPosY -= playerSpeed;
            }

            // Change screen state
            if (IsKeyPressed(KEY_ENTER)) {
                screen = "ENDING";
            }
        }
        else if (screen == "ENDING") {
            // Change screen state
            if (IsKeyPressed(KEY_ENTER)) {
                screen = "TITLE";
            }
        }
        

        //DRAW 
        BeginDrawing();
        if (screen == "TITLE") {
            ClearBackground(bgColor);
            DrawText("Press Enter to Start", (screenWidth / 2 - MeasureText("Press Enter to Start", 80) / 2), 75, 80, txtColor);
        }
        else if (screen == "GAME") {
            ClearBackground(bgColor);
            // Reset player position if out of bounds
            if (playerPosY <= 0) {
                playerPosY = 0;
            }
            if ((playerPosY + playerHeight) >= screenHeight) {
                playerPosY = screenHeight - playerHeight;
            }
 
            DrawRectangle(playerPosX, playerPosY, playerWidth, playerHeight, playerColor);
        }        
        else if (screen == "ENDING") {
            ClearBackground(bgColor);
            DrawText("This is the Ending Screen", (screenWidth / 2 - MeasureText("This is the Ending Screen", 80) / 2), 75, 80, txtColor);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;        
}
