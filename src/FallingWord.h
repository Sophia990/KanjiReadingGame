#pragma once

#include "Word.h"
#include <SFML/Graphics.hpp>
#include <utility>

class FallingWord : public Word, public sf::Drawable {
public:
    FallingWord(sf::String kanji, sf::String kana, sf::String romaji, const sf::Font& font, sf::Vector2f position)
        : Word(std::move(kanji), std::move(kana), std::move(romaji)),
          text(font),
          position(position) {
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setString(getKanji());
        text.setOrigin(text.getLocalBounds().getCenter());
        text.setPosition(position);
    }

    void fall(float dt, float speed);
    bool hasReachedBottom(float bottomY) const;
    bool matches(const sf::String& answer) const;

private:
    sf::Text text;
    sf::Vector2f position;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
