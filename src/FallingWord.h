#ifndef CMAKESFMLPROJECT_FALLINGWORD_H
#define CMAKESFMLPROJECT_FALLINGWORD_H

#include <SFML/Graphics.hpp>
#include "Word.h"

class FallingWord: public Word {

public:
    FallingWord(sf::String kanji,
                sf::String japaneseReading,
                sf::String romajiReading,
                const sf::Font& font,
                sf::Vector2f position)
                : Word(std::move(kanji), std::move(japaneseReading), std::move(romajiReading)),
                       text(font),
                       position(position) {
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setString(getKanji());
        text.setOrigin(text.getLocalBounds().getCenter());
    }

    sf::Vector2f position;

    void drawWord(sf::RenderWindow &window);
    void fall(float dt, float speed, float bottomLine);

private:
    sf::Text text;

    void destroy(bool answeredCorrectly);
};


#endif //CMAKESFMLPROJECT_FALLINGWORD_H
