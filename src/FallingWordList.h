#pragma once

#include "FallingWord.h"
#include "WordList.h"
#include <list>
#include <random>

class FallingWordList : public sf::Drawable {
public:
    void dropWord(std::uniform_real_distribution<float>& xDist,
                  std::mt19937& randomNumberGenerator,
                  const sf::Font& font,
                  WordList& wordList);

    int update(float dt, float speed, float bottomY);

    int submitAnswer(const sf::String& answer);

    void clearWords();

private:
    std::list<FallingWord> fallingWords;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
