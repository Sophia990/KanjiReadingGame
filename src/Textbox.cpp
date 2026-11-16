#include "Textbox.h"

namespace {
    constexpr char32_t backspaceKey = U'\b';
    constexpr char32_t enterKey = U'\r';
    constexpr char32_t minimumKey = 0x20;
    constexpr char32_t deleteKey = 0x7F;
}

sf::String Textbox::handleInput(char32_t unicodeTyped) {
    sf::String answerToReturn;
    if (unicodeTyped == backspaceKey) {
        if (!text.isEmpty()) {
            text.erase(text.getSize() - 1);
        }
    }
    else if (unicodeTyped == enterKey) {
        answerToReturn = text;
        clearText();
    }
    else if (unicodeTyped == deleteKey) {
        clearText();
    }
    else if (unicodeTyped >= minimumKey) {
        text += unicodeTyped;
    }
    textbox.setString(text + "_");
    textbox.setOrigin(textbox.getLocalBounds().getCenter());
    return answerToReturn;
}

void Textbox::setPosition(sf::Vector2f point) {
    textbox.setPosition(point);
}

void Textbox::setLimit(std::size_t lim) {
    limit = lim;
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(textbox, states);
}

void Textbox::clearText() {
    text = "";
    textbox.setString("_");
    textbox.setOrigin(textbox.getLocalBounds().getCenter());
}

sf::String Textbox::handleTypedOn(const sf::Event& input) {
    if (const auto* textEntered = input.getIf<sf::Event::TextEntered>()) {
        const char32_t charTyped = textEntered->unicode;
        if (text.getSize() < limit || charTyped == backspaceKey || charTyped == enterKey || charTyped == deleteKey) {
            return handleInput(charTyped);
        }
    }
    return "";
}
