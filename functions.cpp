#include "functions.h"
#include "namespaces.h"


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
        //Ball::xModifier = -static_cast<double>(0.3f);
        //Ball::yModifier = +static_cast<double>(0.3f);
        Ball::invertY = !Ball::invertY;
        Ball::xModifier = -static_cast<double>(0.05f);
        Ball::yModifier = static_cast<double>(0.05f);
        Ball::center = false;
        std::cerr << "bottom" << "\n";
    }
    Ball::invertX = !Ball::invertX;
}
