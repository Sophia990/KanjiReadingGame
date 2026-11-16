#include "FallingWordList.h"

namespace {
    sf::String toLowerAscii(sf::String text) {
        for (char32_t& c : text) {
            if (c >= U'A' && c <= U'Z') { c += U'a' - U'A'; }
        }
        return text;
    }
} // namespace

void FallingWordList::dropWord(std::uniform_real_distribution<float>& xDist,
                               std::mt19937& randomNumberGenerator,
                               const sf::Font& font,
                               WordList& wordList) {
    if (auto newWord = wordList.takeWord()) {
        const sf::Vector2f position = {xDist(randomNumberGenerator), 0.f};
        fallingWords.emplace_back(newWord->getKanji(), newWord->getKana(), newWord->getRomaji(), font, position);
    }
}

void FallingWordList::update(float dt,
                             float speed,
                             float bottomLine,
                             const sf::String& answer,
                             int& points,
                             int& lives,
                             sf::Sound& correctSound,
                             sf::Sound& incorrectSound) {
    const sf::String loweredAnswer = toLowerAscii(answer);
    for (auto word = fallingWords.begin(); word != fallingWords.end();) {
        word->fall(dt, speed, bottomLine, points, lives, correctSound, incorrectSound);
        if (!loweredAnswer.isEmpty() && (loweredAnswer == word->getKana() || loweredAnswer == word->getRomaji())) {
            word->destroy(true, points, lives, correctSound, incorrectSound);
        }
        if (word->getShouldDestroy()) {
            word = fallingWords.erase(word);
        } else {
            ++word;
        }
    }
}

void FallingWordList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const FallingWord& word : fallingWords) { target.draw(word, states); }
}

void FallingWordList::clearWords() { fallingWords.clear(); }
