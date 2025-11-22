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
    constexpr int playerSpeed {25};    
    constexpr Color playerColor {WHITE}; 

    //player 1 variables (refactor when I learn structs or classes in CPP)
    constexpr float player1PosX {100};
    float player1PosY {(screenHeight / 2) - playerHeight};    
    Rectangle player1Bounds = {player1PosX, player1PosY, playerWidth, playerHeight};

    //player 2 variables (same as above)
    constexpr float player2PosX {screenWidth - 100};
    float player2PosY {(screenHeight / 2) - playerHeight};    
    Rectangle player2Bounds = {player2PosX, player2PosY, playerWidth, playerHeight};


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
            if (IsKeyDown(KEY_S)) {
                player1PosY += playerSpeed;
            }
            if (IsKeyDown(KEY_W)) {
                player1PosY -= playerSpeed;
            }
            if (IsKeyDown(KEY_DOWN)) {
                player2PosY += playerSpeed;
            }
            if (IsKeyDown(KEY_UP)) {
                player2PosY -= playerSpeed;
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
            player1Bounds = {player1PosX, player1PosY, playerWidth, playerHeight};
            player2Bounds = {player2PosX, player2PosY, playerWidth, playerHeight};
            ballBounds = {ballPosX, ballPosY, ballWidth, ballHeight};
            if (CheckCollisionRecs(player1Bounds, ballBounds) || CheckCollisionRecs(player2Bounds, ballBounds)) {
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
            if (player1PosY <= 0) {
                player1PosY = 0;
            }
            if ((player1PosY + playerHeight) >= screenHeight) {
                player1PosY = screenHeight - playerHeight;
            }
            if (player2PosY <= 0) {
                player2PosY = 0;
            }
            if ((player2PosY + playerHeight) >= screenHeight) {
                player2PosY = screenHeight - playerHeight;
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
 
            DrawRectangle(player1PosX, static_cast<int>(player1PosY), playerWidth, playerHeight, playerColor);
            DrawRectangle(player2PosX, static_cast<int>(player2PosY), playerWidth, playerHeight, playerColor);
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
