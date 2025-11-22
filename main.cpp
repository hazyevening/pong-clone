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
    constexpr float playerHeight {100};
    constexpr float playerWidth {20};
    constexpr float playerPosX {100};
    float playerPosY {(screenHeight / 2) - playerHeight};    
    constexpr int playerSpeed {25};    
    Rectangle playerBounds = {playerPosX, playerPosY, playerWidth, playerHeight};
    constexpr Color playerColor {WHITE}; 

    // ball variables
    constexpr float ballWidth {15};
    constexpr float ballHeight {15};
    float ballPosX {(screenWidth / 2) - ballWidth};
    float ballPosY {(screenHeight / 2) - ballHeight};
    float ballSpeed {10};
    bool invertBallDirectionV {false};
    bool invertBallDirectionH {false};
    Rectangle ballBounds = {ballPosX, ballPosY, ballWidth, ballHeight};
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


            // Invert ball direction if it hits the screen vertical boundaries
            if (!invertBallDirectionV) {
                ballPosY += ballSpeed;
            }
            else {
                ballPosY -= ballSpeed;
            }
            // Invert ball direction if it hits a paddle
            if (!invertBallDirectionH) {
                ballPosX -= ballSpeed;
            }
            else {
                ballPosX += ballSpeed;
            }

            // Detect player input
            if (IsKeyDown(KEY_DOWN)) {
                playerPosY += playerSpeed;
            }
            if (IsKeyDown(KEY_UP)) {
                playerPosY -= playerSpeed;
            }


            /* std::cerr << "Player position X: " << playerPosX << "\n";
            std::cerr << "Player position Y: " << playerPosY << "\n";
            std::cerr << "Player width: " << playerWidth << "\n";
            std::cerr << "Player height: " << playerHeight << "\n";   

            std::cerr << "Ball position X: " << ballPosX << "\n";
            std::cerr << "Ball position X: " << ballPosY << "\n";
            std::cerr << "Ball width: " << ballWidth << "\n";
            std::cerr << "Ball height: " << ballHeight << "\n"; */

            // Collision bs
            playerBounds = {playerPosX, playerPosY, playerWidth, playerHeight};
            ballBounds = {ballPosX, ballPosY, ballWidth, ballHeight};
            if (CheckCollisionRecs(playerBounds, ballBounds)) {
               invertBallDirectionH = !invertBallDirectionH; 
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
                std::cerr << invertBallDirectionV;
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
 
            DrawRectangle(playerPosX, static_cast<int>(playerPosY), playerWidth, playerHeight, playerColor);
            DrawRectangle(static_cast<int>(ballPosX), static_cast<int>(ballPosY), ballWidth, ballHeight, ballColor);
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
