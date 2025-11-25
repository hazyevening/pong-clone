#include <iostream>
#include "raylib.h"
#include <string> 

namespace Interface {
    constexpr int screenWidth {1920};
    constexpr int screenHeight {1080};
    constexpr Color txtColor {WHITE};
    constexpr Color bgColor {BLACK};
}

// Refactor namespaces when I learn Classes
namespace Players {
    // general player variables
    constexpr float height {150};
    constexpr float width {20};
    constexpr int speed {25};    
    constexpr Color color {WHITE}; 
    
}

namespace Player1 {
    constexpr float x {100};
    float y {(Interface::screenHeight / 2) - Players::height};    
    Rectangle player1Bounds = {Player1::x, Player1::y, Players::width, Players::height};
}

namespace Player2{
    constexpr float x {Interface::screenWidth - 100};
    float y {(Interface::screenHeight / 2) - Players::height};        
    Rectangle player2Bounds = {Player2::x, Player2::y, Players::width, Players::height};
}

namespace Ball {
    constexpr float width {15};
    constexpr float height {15};
    float x {(Interface::screenWidth / 2) - Ball::width};
    float y {(Interface::screenHeight / 2) - Ball::height};
    float speed {15};    
    float xModifier {0};
    float yModifier {0};
    bool invertY {false};
    bool invertX {false};
    Rectangle bounds = {Ball::x, Ball::y, Ball::width, Ball::height};
    constexpr Color color {WHITE};
    
}



float calcBallPosX(bool invert, bool xModifier, float speed) {

    if (invert) {
        speed = -(speed + xModifier);
    }
    else if (!invert) {
        speed += xModifier;
    }

    return speed;
}

float calcBallPosY(bool invert, bool yModifier, float speed) {

    if (invert) {
        speed = -(speed + yModifier);
    }
    else if (!invert) {
        speed += yModifier;
    }

    return speed;
}

void collisionLogic() {
    Ball::invertX = !Ball::invertX;
}

/*

float checkSubCollision(Rectangle playerBounds, Rectangle ballBounds) {
    Rectangle playerTopHalf = {playerBounds.x, playerBounds.y, playerBounds.width, playerBounds.height / 2 + playerBounds.y};
    Rectangle playerBottomHalf = {playerBounds.x, (playerBounds.height / 2) + playerBounds.y, playerBounds.width, (playerBounds.height) + playerBounds.y};
    // Rectangle(float x, float y, float width, float height)
    
    if (CheckCollisionRecs(playerTopHalf, ballBounds)) {
        return 0.0f;   
    }
    else if (CheckCollisionRecs(playerBottomHalf, ballBounds)){
        return 50.0f; 
    }
    else {
        return 50000000000000.0f;    
    }
} */

int main() {

    std::string screen {"TITLE"};

    int framesCounter {};

    InitWindow(Interface::screenWidth, Interface::screenHeight, "raylib test");
    SetTargetFPS(60);    

    // Game Loop
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
        

            // Update ball position
            Ball::x += (calcBallPosX(Ball::invertX, Ball::xModifier, Ball::speed));
            Ball::y += (calcBallPosY(Ball::invertY, Ball::yModifier, Ball::speed));

            // Collision bs
            Player1::player1Bounds = {Player1::x, Player1::y, Players::width, Players::height};
            Player2::player2Bounds = {Player2::x, Player2::y, Players::width, Players::height};
            Ball::bounds = {Ball::x, Ball::y, Ball::width, Ball::height};

            
            if (CheckCollisionRecs(Player1::player1Bounds, Ball::bounds) || CheckCollisionRecs(Player2::player2Bounds, Ball::bounds)){
                collisionLogic();
            }            
            

         /*   if (CheckCollisionRecs(player1Bounds, ballBounds)) {
                invertBallDirectionH = !invertBallDirectionH;
                xModifier = checkSubCollision(player1Bounds, ballBounds);
            }
            else if (CheckCollisionRecs(player2Bounds, ballBounds)) {
                invertBallDirectionH = !invertBallDirectionH;
                xModifier = -checkSubCollision(player2Bounds, ballBounds);
            } */

            // Detect input and update player position
            if (IsKeyDown(KEY_S)) {
                Player1::y += Players::speed;
            }
            if (IsKeyDown(KEY_W)) {
                Player1::y -= Players::speed;
            }
            if (IsKeyDown(KEY_DOWN)) {
                Player2::y += Players::speed;
            }
            if (IsKeyDown(KEY_UP)) {
                Player2::y -= Players::speed;
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
            ClearBackground(Interface::bgColor);
            DrawText("Press Enter to Start", (Interface::screenWidth / 2 - MeasureText("Press Enter to Start", 80) / 2), 75, 80, Interface::txtColor);
        }
        else if (screen == "GAME") {
            ClearBackground(Interface::bgColor);
            // Reset player position if out of bounds
            if (Player1::y <= 0) {
                Player1::y = 0;
            }
            if ((Player1::y + Players::height) >= Interface::screenHeight) {
                Player1::y = Interface::screenHeight - Players::height;
            }
            if (Player2::y <= 0) {
                Player2::y = 0;
            }
            if ((Player2::y + Players::height) >= Interface::screenHeight) {
                Player2::y = Interface::screenHeight - Players::height;
            }

            // Reset ball position if out of vertical bounds
            if (Ball::y <= 0) {
                Ball::y = 0;
                Ball::invertY = !Ball::invertY;
            }
            if (Ball::y + Ball::height >= Interface::screenHeight) {
                Ball::y = Interface::screenHeight - Ball::height;
                Ball::invertY = !Ball::invertY;
            }
            // Reset screen state if ball goes out of horizontal bounds
            if (Ball::x <= 0 || (Ball::x + Ball::width) >= Interface::screenWidth){
                Ball::x = (Interface::screenWidth / 2) - Ball::width;
                Ball::y = (Interface::screenHeight / 2) - Ball::height;
            }
 
            DrawRectangle(Player1::x, static_cast<int>(Player1::y), Players::width, Players::height, Players::color);
            DrawRectangle(Player2::x, static_cast<int>(Player2::y), Players::width, Players::height, Players::color);
            DrawRectangle(static_cast<int>(Ball::x), static_cast<int>(Ball::y), Ball::width, Ball::height, Ball::color);
        }        
        else if (screen == "ENDING") {
            ClearBackground(Interface::bgColor);
            DrawText("This is the Ending Screen", (Interface::screenWidth / 2 - MeasureText("This is the Ending Screen", 80) / 2), 75, 80, Interface::txtColor);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;        
}
