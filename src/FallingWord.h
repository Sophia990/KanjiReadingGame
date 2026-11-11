#ifndef CMAKESFMLPROJECT_FALLINGWORD_H
#define CMAKESFMLPROJECT_FALLINGWORD_H

#include <SFML/Graphics.hpp>
#include "Word.h"

class FallingWord: public Word {

public:
    FallingWord(sf::String kanji,
                sf::String japaneseReading,
                sf::String romajiReading,
                const sf::Font& font)
                : Word(std::move(kanji), std::move(japaneseReading), std::move(romajiReading)),
                       text(font) {
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setString(getKanji());
    }

    sf::Vector2f position = {0.f, 0.f};

    void drawWord(sf::RenderWindow &window);

private:
    sf::Text text;
};


#endif //CMAKESFMLPROJECT_FALLINGWORD_H
