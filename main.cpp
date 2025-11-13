#include <iostream>
#include "raylib.h"
#include <string> 





int main() {

    std::string screen {"TITLE"};

    int framesCounter {};

    // interface variables
    constexpr int screenWidth {1920};
    constexpr int screenHeight {1080};
    constexpr Color txtColor {WHITE};
    constexpr Color bgColor {BLACK};

    // player variables
    constexpr int playerHeight {100};
    constexpr int playerWidth {20};
    constexpr int playerPosX {100};    
    int playerPosY {(screenHeight / 2) - playerHeight};    
    constexpr int playerSpeed {25};    
    constexpr Color playerColor {WHITE}; 

    // ball variables
    constexpr int ballWidth {15};
    constexpr int ballHeight {15};
    int ballPosX {(screenWidth / 2) - ballWidth};
    int ballPosY {(screenHeight / 2) - ballHeight};
    int ballSpeed {10};
    bool invertBallDirectionV {false};
    constexpr Color ballColor {WHITE};
    
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

            ballPosX -= ballSpeed;
            if (!invertBallDirectionV) {
                ballPosY += ballSpeed;
            }
            else {
                ballPosY -= ballSpeed;
            }

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

            // Reset ball position if out of vertical bounds
            if (ballPosY <= 0) {
                ballPosY = 0;
                invertBallDirectionV = !invertBallDirectionV;
            }
            if (ballPosY + ballHeight >= screenHeight) {
                ballPosY = screenHeight - ballHeight;
                invertBallDirectionV = !invertBallDirectionV;
            }
            // Reset screen state if ball goes out of horizontal bounds
            if (ballPosX <= 0 || (ballPosX + ballWidth) >= screenWidth){
                ballPosX = (screenWidth / 2) - ballWidth;
                ballPosY = (screenHeight / 2) - ballHeight;
            }
 
            DrawRectangle(playerPosX, playerPosY, playerWidth, playerHeight, playerColor);
            DrawRectangle(ballPosX, ballPosY, ballWidth, ballHeight, ballColor);
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
