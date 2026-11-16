#include "FallingWordList.h"

namespace {
    // ensure that romaji answers are case-insensitive
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

// returns number of lives lost
int FallingWordList::update(float dt, float speed, float bottomY) {
    for (FallingWord& word : fallingWords) { word.fall(dt, speed); }

    const auto before = fallingWords.size();
    fallingWords.remove_if([bottomY](const FallingWord& word) { return word.hasReachedBottom(bottomY); });
    return static_cast<int>(before - fallingWords.size());
}

// returns number of points earned
int FallingWordList::submitAnswer(const sf::String& answer) {
    const sf::String loweredAnswer = toLowerAscii(answer);
    if (loweredAnswer.isEmpty()) return 0;

    const auto before = fallingWords.size();
    fallingWords.remove_if([&loweredAnswer](const FallingWord& word) { return word.matches(loweredAnswer); });
    return static_cast<int>(before - fallingWords.size());
}

void FallingWordList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const FallingWord& word : fallingWords) { target.draw(word, states); }
}

void FallingWordList::clearWords() { fallingWords.clear(); }
