#pragma once

#include <SFML/System/String.hpp>
#include <utility>

class Word {

public:
    Word(sf::String kanji,
         sf::String kana,
         sf::String romaji)
         : kanji(std::move(kanji)),
           kana(std::move(kana)),
           romaji(std::move(romaji)) {}

    const sf::String& getKanji() const;
    const sf::String& getKana() const;
    const sf::String& getRomaji() const;

private:
    sf::String kanji;
    sf::String kana;
    sf::String romaji;
};
