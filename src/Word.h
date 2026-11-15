#pragma once

#include <SFML/Graphics.hpp>
#include <utility>

class Word {

public:
    Word(sf::String kanji,
         sf::String kana,
         sf::String romaji)
         : kanji(std::move(kanji)),
           kana(std::move(kana)),
           romaji(std::move(romaji)) {}

    sf::String getKanji();
    sf::String getKana();
    sf::String getRomaji();

private:
    sf::String kanji;
    sf::String kana;
    sf::String romaji;
};
