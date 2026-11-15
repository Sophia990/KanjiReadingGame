#pragma once

#include <list>
#include <random>
#include "FallingWord.h"
#include "WordList.h"

class FallingWordList {
public:
    void dropWord(std::uniform_real_distribution<float> &xDist,
                             std::mt19937 &randomNumberGenerator,
                             const sf::Font &font,
                             WordList &wordList);

    void update(float dt, float speed, float bottomLine, const sf::String& answer, int& points, int& lives, sf::Sound& correctSound, sf::Sound& incorrectSound);

    void drawWords(sf::RenderWindow &window);

    void clearWords();

private:
    std::list<FallingWord> fallingWordList;
};
