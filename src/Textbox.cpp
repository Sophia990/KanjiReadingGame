#include "Textbox.h"

#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define MINIMUM_KEY 32
#define DELETE_KEY 127

sf::String Textbox::getText() {
    return text;
}

sf::String Textbox::handleInput(std::uint32_t unicodeTyped) {
    sf::String answerToReturn = "";
    if (unicodeTyped == BACKSPACE_KEY) {
        if (!text.isEmpty()) {
            text.erase(text.getSize() - 1);
        }
    }
    else if (unicodeTyped == ENTER_KEY) {
        answerToReturn = text;
        clearText();
    }
    else if (unicodeTyped == DELETE_KEY) {
        clearText();
    }
    else if (unicodeTyped >= MINIMUM_KEY) {
        text += static_cast<char32_t>(unicodeTyped);
    }
    textbox.setString(text + "_");
    textbox.setOrigin(textbox.getLocalBounds().getCenter());
    return answerToReturn;
}

void Textbox::setPosition(sf::Vector2f point) {
    textbox.setPosition(point);
}

void Textbox::setLimit(size_t lim) {
    limit = lim;
}

void Textbox::drawTextbox(sf::RenderWindow &window) {
    window.draw(textbox);
}

void Textbox::clearText() {
    text = "";
    textbox.setString("_");
    textbox.setOrigin(textbox.getLocalBounds().getCenter());
}

sf::String Textbox::handleTypedOn(const sf::Event& input) {
    if (const auto* textEntered = input.getIf<sf::Event::TextEntered>()) {
        int charTyped = static_cast<int>(textEntered->unicode);
        if (text.getSize() < limit || charTyped == BACKSPACE_KEY || charTyped == ENTER_KEY || charTyped == DELETE_KEY) {
            return handleInput(charTyped);
        }
    }
    return "";
}
