#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <utility>
#include "Word.h"

class FallingWord: public Word, public sf::Drawable {

public:
    FallingWord(sf::String kanji,
                sf::String kana,
                sf::String romaji,
                const sf::Font& font,
                sf::Vector2f position)
                : Word(std::move(kanji), std::move(kana), std::move(romaji)),
                       text(font),
                       position(position) {
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setString(getKanji());
        text.setOrigin(text.getLocalBounds().getCenter());
        text.setPosition(position);
    }

    bool getShouldDestroy() const;
    void fall(float dt, float speed, float bottomLine, int& points, int& lives, sf::Sound& correctSound, sf::Sound& incorrectSound);
    void destroy(bool answeredCorrectly, int& points, int& lives, sf::Sound& correctSound, sf::Sound& incorrectSound);

private:
    sf::Text text;
    bool shouldDestroy = false;
    sf::Vector2f position;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
