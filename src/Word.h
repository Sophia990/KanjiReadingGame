#ifndef CMAKESFMLPROJECT_WORD_H
#define CMAKESFMLPROJECT_WORD_H

#include <SFML/Graphics.hpp>
#include <utility>

class Word {

public:
    Word(sf::String kanji,
         sf::String japaneseReading,
         sf::String romajiReading)
         : kanji(std::move(kanji)),
         japaneseReading(std::move(japaneseReading)),
         romajiReading(std::move(romajiReading)) {}

    sf::String getKanji();
    sf::String getJapaneseReading();
    sf::String getRomajiReading();

private:
    sf::String kanji;
    sf::String japaneseReading;
    sf::String romajiReading;
};


#endif //CMAKESFMLPROJECT_WORD_H
