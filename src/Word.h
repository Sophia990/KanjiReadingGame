#pragma once

#include <SFML/System/String.hpp>
#include <utility>

class Word {
public:
    Word(sf::String kanji, sf::String kana, sf::String romaji)
        : kanji(std::move(kanji)),
          kana(std::move(kana)),
          romaji(std::move(romaji)) {}

    [[nodiscard]] const sf::String& getKanji() const;
    [[nodiscard]] const sf::String& getKana() const;
    [[nodiscard]] const sf::String& getRomaji() const;

private:
    sf::String kanji;
    sf::String kana;
    sf::String romaji;
};
