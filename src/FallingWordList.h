#ifndef CMAKESFMLPROJECT_FALLINGWORDLIST_H
#define CMAKESFMLPROJECT_FALLINGWORDLIST_H

#include <list>
#include <random>
#include "FallingWord.h"
#include "WordList.h"

class FallingWordList {
public:
    std::list<FallingWord> fallingWordList;

    void dropWord(std::uniform_real_distribution<float> &xDist,
                             std::uniform_int_distribution<int> &wordDist,
                             std::mt19937 &randomNumberGenerator,
                             const sf::Font &font,
                             const WordList &wordList);

    void update(float dt, float speed, float bottomLine, const sf::String& answer, int& points, int& lives);
};


#endif //CMAKESFMLPROJECT_FALLINGWORDLIST_H
