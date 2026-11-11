#include "FallingWord.h"

void FallingWord::drawWord(sf::RenderWindow &window) {
    text.setPosition(position);
    window.draw(text);
}

void FallingWord::fall(float dt, float speed, float bottomLine) {
    position.y += speed * dt;
    if (position.y <= bottomLine) {
        destroy(false);
    }
}

void FallingWord::destroy(bool answeredCorrectly) {
    // TODO remove from list of falling words later
}