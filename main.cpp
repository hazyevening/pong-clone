#include <iostream>
#include "raylib.h"
#include "namespaces.h"
#include <string> 

void updateScore(bool invert) {
    if (!invert) {
        Player1::score ++;
    }
    else {
        Player2::score ++;
    }
}


void checkWinCondition() {
    if (Player1::score >= Interface::winScore) {
        Interface::screen = "ENDING";
        Interface::winner = "p1";
    }
    else if (Player2::score >= Interface::winScore) {
        Interface::screen = "ENDING";
        Interface::winner = "p2";
    }
    else {
        ;      
    }
}


float calcBallPosX(float speed) {
    if (Ball::invertX) {
        speed = -(speed * (1.0f + Ball::xModifier));
    }
    else if (!Ball::invertX) {
        speed *= (1.0f + Ball::xModifier);
    }

    return speed;
}


float calcBallPosY(float speed) {
    if (Ball::center) {
        speed = 0;
    }
    else if (Ball::invertY) {
        speed = -(speed * (1.0f + Ball::yModifier));
    }
    else if (!Ball::invertY) {
        speed *= (1.0f + Ball::yModifier);
    }

    return speed;
}


void collisionLogic(std::string player) {
    Rectangle top{};
    Rectangle centerTop{};
    Rectangle center{};
    Rectangle centerBottom{};
    Rectangle bottom{};

    constexpr float oneFifthHeight {Players::height / 5};

    if (player == "p1") {
        top = {Player1::x, Player1::y, Players::width, oneFifthHeight};
        centerTop = {Player1::x, oneFifthHeight + Player1::y, Players::width, oneFifthHeight};
        center = {Player1::x, oneFifthHeight * 2 + Player1::y, Players::width, oneFifthHeight};
        centerBottom = {Player1::x, oneFifthHeight * 3 + Player1::y, Players::width, oneFifthHeight};
        bottom = {Player1::x, oneFifthHeight * 4 + Player1::y, Players::width, oneFifthHeight};
    }
    else if (player == "p2") {
        top = {Player2::x, Player2::y, Players::width, oneFifthHeight};
        centerTop = {Player2::x, oneFifthHeight + Player2::y, Players::width, oneFifthHeight};
        center = {Player2::x, oneFifthHeight * 2 + Player2::y, Players::width, oneFifthHeight};
        centerBottom = {Player2::x, oneFifthHeight * 3 + Player2::y, Players::width, oneFifthHeight};
        bottom = {Player2::x, oneFifthHeight * 4 + Player2::y, Players::width, oneFifthHeight};
    }
    else {
        std::cerr << "wtf";
    }      
    

    if (CheckCollisionRecs(top, Ball::bounds)) {
        Ball::invertY = !Ball::invertY;
        Ball::xModifier = static_cast<double>(0.05f);
        Ball::yModifier = -static_cast<double>(0.05f);
        Ball::center = false;
    }
    else if (CheckCollisionRecs(centerTop, Ball::bounds)) {
        Ball::xModifier = static_cast<double>(0.15f);
        Ball::yModifier = -static_cast<double>(0.15f);
        Ball::center = false;
    }
    else if (CheckCollisionRecs(center, Ball::bounds)) {
        Ball::center = true;
    }
    else if (CheckCollisionRecs(centerBottom, Ball::bounds)) {
        Ball::xModifier = -static_cast<double>(0.15f);
        Ball::yModifier = +static_cast<double>(0.15f);
        Ball::center = false;
    }
    else {
        Ball::invertY = !Ball::invertY;
        Ball::xModifier = -static_cast<double>(0.05f);
        Ball::yModifier = static_cast<double>(0.05f);
        Ball::center = false;
        std::cerr << "bottom" << "\n";
    }
    Ball::invertX = !Ball::invertX;
}


void updatePlayerPosition() {
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
}

int main() {
    int framesCounter {};

    InitWindow(Interface::screenWidth, Interface::screenHeight, "raylib test");
    SetTargetFPS(60);    

    // Game Loop
    while (!WindowShouldClose()) {

        //UPDATE    
        if (Interface::screen == "TITLE") {
            ++framesCounter;
            // Change screen state
            if (IsKeyPressed(KEY_ENTER)) {
                Interface::screen = "GAME";
            }
        }
        else if (Interface::screen == "GAME") {
            ++framesCounter;

        
            // Collision detection and logic
            Player1::bounds = {Player1::x, Player1::y, Players::width, Players::height};
            Player2::bounds = {Player2::x, Player2::y, Players::width, Players::height};
            Ball::bounds = {Ball::x, Ball::y, Ball::width, Ball::height};
            
            if (CheckCollisionRecs(Player1::bounds, Ball::bounds)) {
                collisionLogic("p1");
            } else if (CheckCollisionRecs(Player2::bounds, Ball::bounds)) {
                collisionLogic("p2");
            }            

            // Update ball position
            Ball::x += (calcBallPosX(Ball::speed));
            Ball::y += (calcBallPosY(Ball::speed));

            updatePlayerPosition();

            // Reset paddles position if out of vertical bounds
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

            // Reset screen state if ball goes out of horizontal bounds and update score
            if (Ball::x <= 0 || (Ball::x + Ball::width) >= Interface::screenWidth){
                Ball::x = (Interface::screenWidth / 2) - Ball::width;
                Ball::y = (Interface::screenHeight / 2) - Ball::height;
                Ball::xModifier = 0;
                Ball::yModifier = 0;
                Ball::center = false;
                updateScore(Ball::invertX);
                checkWinCondition();
            }
        }
        else if (Interface::screen == "ENDING") {
            // Change screen state
            if (IsKeyPressed(KEY_ENTER)) {
                Interface::screen = "GAME";
            }
        }
        

        //DRAW 
        BeginDrawing();
        if (Interface::screen == "TITLE") {
            ClearBackground(Interface::bgColor);
            DrawText("Press Enter to Start", (Interface::screenWidth / 2 - MeasureText("Press Enter to Start", 80) / 2), 75, Interface::txtSize, Interface::txtColor);
        }
        else if (Interface::screen == "GAME") {
            ClearBackground(Interface::bgColor);
            // Reset player position if out of bounds
            DrawText(TextFormat("%i", Player1::score), (Interface::screenWidth / 4 - MeasureText(TextFormat("%i", Player1::score), 80) / 2), 75, Interface::txtSize, Interface::txtColor);
            DrawText(TextFormat("%i", Player2::score), (Interface::screenWidth - (Interface::screenWidth / 4) - MeasureText(TextFormat("%i", Player2::score), 80) / 2), 75, Interface::txtSize, Interface::txtColor);
 
            DrawRectangle(Player1::x, static_cast<int>(Player1::y), Players::width, Players::height, Players::color); 
            DrawRectangle(Player2::x, static_cast<int>(Player2::y), Players::width, Players::height, Players::color);
            DrawRectangle(static_cast<int>(Ball::x), static_cast<int>(Ball::y), Ball::width, Ball::height, Ball::color);
        }        
        else if (Interface::screen == "ENDING") {
            ClearBackground(Interface::bgColor);
            if (Interface::winner == "p1") {
                DrawText("Congratulations Player 1!", (Interface::screenWidth / 2 - MeasureText("Congratulations Player 1", 80) / 2), 75, 80, Interface::txtColor);
            }
            else {
                DrawText("Congratulations Player 2!", (Interface::screenWidth / 2 - MeasureText("Congratulations Player 1", 80) / 2), 75, 80, Interface::txtColor);
            }
            DrawText("Press Enter to Play Again", (Interface::screenWidth / 2 - MeasureText("Press Enter to Play Again", Interface::txtSize) / 2 ), (Interface::screenHeight - (Interface::screenHeight / 9)), Interface::txtSize, Interface::txtColor);
            Player1::score = 0;
            Player2::score = 0;
            
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;        
}
