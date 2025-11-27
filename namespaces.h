#ifndef NAMESPACES_H
#define NAMESPACES_H

// Refactor namespaces when I learn Classes
namespace Interface {
    constexpr int screenWidth {1920};
    constexpr int screenHeight {1080};
    constexpr Color txtColor {WHITE};
    constexpr int txtSize {80};
    constexpr Color bgColor {BLACK};
}

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
    Rectangle bounds = {Player1::x, Player1::y, Players::width, Players::height};
}

namespace Player2{
    constexpr float x {Interface::screenWidth - 100};
    float y {(Interface::screenHeight / 2) - Players::height};        
    Rectangle bounds = {Player2::x, Player2::y, Players::width, Players::height};
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

#endif
