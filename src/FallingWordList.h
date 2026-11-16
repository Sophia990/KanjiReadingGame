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

    void update(float dt,
                float speed,
                float bottomLine,
                const sf::String& answer,
                int& points,
                int& lives,
                sf::Sound& correctSound,
                sf::Sound& incorrectSound);

    void clearWords();

private:
    std::list<FallingWord> fallingWords;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
