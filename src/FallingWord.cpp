#include "FallingWord.h"

void FallingWord::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(text, states); }

void FallingWord::fall(float dt,
                       float speed,
                       float bottomLine,
                       int& points,
                       int& lives,
                       sf::Sound& correctSound,
                       sf::Sound& incorrectSound) {
    position.y += (speed + (static_cast<float>(points)) * 5) * dt;
    text.setPosition(position);
    if (position.y >= bottomLine) { destroy(false, points, lives, correctSound, incorrectSound); }
}

void FallingWord::destroy(
    bool answeredCorrectly, int& points, int& lives, sf::Sound& correctSound, sf::Sound& incorrectSound) {
    shouldDestroy = true;
    if (answeredCorrectly) {
        points++;
        correctSound.play();
    } else {
        if (lives > 0) lives--;
        incorrectSound.play();
    }
}

bool FallingWord::getShouldDestroy() const { return shouldDestroy; }
