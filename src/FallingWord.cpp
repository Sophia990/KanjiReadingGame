#include "FallingWord.h"

void FallingWord::drawWord(sf::RenderWindow &window) {
    text.setPosition(position);
    window.draw(text);
}

void FallingWord::fall(float dt, float speed, float bottomLine, int& points, int& lives) {
    position.y += (speed + (static_cast<float>(points)) * 5) * dt;
    if (position.y >= bottomLine) {
        destroy(false, points, lives);
    }
}

void FallingWord::destroy(bool answeredCorrectly, int& points, int& lives) {
    shouldDestroy = true;
    if (answeredCorrectly) {
        points++;
    } else {
        lives--;
    }
}

bool FallingWord::getShouldDestroy() const {return shouldDestroy;}