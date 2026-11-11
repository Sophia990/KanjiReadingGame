//
// Created by Sophia on 11/11/2026.
//

#include <iostream>
#include "FallingWord.h"

void FallingWord::drawWord(sf::RenderWindow &window) {
    text.setPosition(position);
    window.draw(text);
}