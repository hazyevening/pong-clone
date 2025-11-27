#include <iostream>
#include "raylib.h"
#include <string> 
#include "namespaces.h"



float calcBallPosX(float speed) {
    if (Ball::invertX) {
        speed = -(speed * (1.0f + Ball::xModifier));
    }
    else if (!Ball::invertX) {
        speed *= (1.0f + Ball::xModifier);
    }

    //std::cerr << "Ball xModifier inside calcPosX: " << Ball::xModifier << "\n";
    //std::cerr << "Ball yModifier inside calcPosX: " << Ball::yModifier << "\n";
    return speed;
}


float calcBallPosY(float speed) {
    if (Ball::invertY) {
        speed = -(speed * (1.0f + Ball::yModifier));
    }
    else if (!Ball::invertY) {
        speed *= (1.0f + Ball::yModifier);
    }

    //std::cerr << "Ball xModifier inside calcPosY: " << Ball::xModifier << "\n";
    //std::cerr << "Ball yModifier inside calcPosY: " << Ball::yModifier << "\n";
    return speed;
}


void collisionLogic(std::string player) {
    Rectangle top{};
    Rectangle centerTop{};
    Rectangle centerBottom{};
    Rectangle bottom{};

    constexpr float quarterHeight {Players::height / 4};
    constexpr float halfHeight {Players::height / 2};
    constexpr float threeQuarterHeight {halfHeight + quarterHeight};

    if (player == "p1") {
        top = {Player1::x, Player1::y, Players::width, quarterHeight};
        centerTop = {Player1::x, quarterHeight + Player1::y, Players::width, quarterHeight};
        centerBottom = {Player1::x, halfHeight + Player1::y, Players::width, quarterHeight};
        bottom = {Player1::x, threeQuarterHeight + Player1::y, Players::width, quarterHeight};
    }
    else if (player == "p2") {
        top = {Player2::x, Player2::y, Players::width, quarterHeight};
        centerTop = {Player2::x, quarterHeight + Player2::y, Players::width, quarterHeight};
        centerBottom = {Player2::x, halfHeight + Player2::y, Players::width, quarterHeight};
        bottom = {Player2::x, threeQuarterHeight + Player2::y, Players::width, quarterHeight};
    }
    else {
        std::cerr << "wtf";
    }    

    std::cerr << "top pos y: " << top.y << "\n";
    std::cerr << "top height: " << top.height << "\n";

    std::cerr << "center-top pos y: " << centerTop.y << "\n";
    std::cerr << "center-top height: " << centerTop.height << "\n";

    std::cerr << "center-bottom y: " << centerBottom.y << "\n";    
    std::cerr << "center-bottom height: : " << centerBottom.height << "\n";

    std::cerr << "bottom pos y: " << bottom.y << "\n";
    std::cerr << "bottom height: " << bottom.height << "\n";

    std::cerr << "ball pos y: " << Ball::y << "\n";
    if (CheckCollisionRecs(top, Ball::bounds)) {
        Ball::xModifier = static_cast<double>(0.3f);
        Ball::yModifier = -static_cast<double>(0.3f);
        std::cerr << "top" << "\n";
    }
    else if (CheckCollisionRecs(centerTop, Ball::bounds)) {
        Ball::xModifier = static_cast<double>(0.3f);
        Ball::yModifier = -static_cast<double>(0.3f);
        std::cerr << "centerTop" << "\n";
    }
    else if (CheckCollisionRecs(centerBottom, Ball::bounds)) {
        Ball::xModifier = -static_cast<double>(0.3f);
        Ball::yModifier = +static_cast<double>(0.3f);
        std::cerr << "centerBottom" << "\n";
    }
    else {
        Ball::xModifier = -static_cast<double>(0.3f);
        Ball::yModifier = +static_cast<double>(0.3f);
        std::cerr << "bottom" << "\n";
    }
    Ball::invertX = !Ball::invertX;
}

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
            // std::cerr << "Ball speed before calcPosX: " << Ball::speed << "\n";
            Ball::x += (calcBallPosX(Ball::speed));
            // std::cerr << "Ball speed after calcPosX: " << Ball::speed << "\n";
            Ball::y += (calcBallPosY(Ball::speed));

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
            DrawText("Press Enter to Start", (Interface::screenWidth / 2 - MeasureText("Press Enter to Start", 80) / 2), 75, Interface::txtSize, Interface::txtColor);
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
