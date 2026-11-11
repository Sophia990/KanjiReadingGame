#include "Textbox.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

sf::String Textbox::getText() {
    return text;
}

sf::String Textbox::handleInput(std::uint32_t unicodeTyped) {
    sf::String answerToReturn = "";
    if (unicodeTyped == DELETE_KEY) {
        if (!text.isEmpty()) {
            text.erase(text.getSize() - 1);
        }
    }
    else if (unicodeTyped == ENTER_KEY) {
        answerToReturn = text;
        text = "";
    }
    else if (unicodeTyped != ESCAPE_KEY) {
        text += static_cast<char32_t>(unicodeTyped);
    }
    textbox.setString(text + "_");
    textbox.setOrigin(textbox.getLocalBounds().getCenter());
    return answerToReturn;
}

void Textbox::setPosition(sf::Vector2f point) {
    textbox.setPosition(point);
}

void Textbox::setLimit(int lim) {
    limit = lim - 1;
}

void Textbox::drawTextbox(sf::RenderWindow &window) {
    window.draw(textbox);
}

sf::String Textbox::handleTypedOn(const sf::Event& input) {
    if (const auto* textEntered = input.getIf<sf::Event::TextEntered>()) {
        int charTyped = static_cast<int>(textEntered->unicode);
        if (text.getSize() <= limit || charTyped == DELETE_KEY || charTyped == ENTER_KEY) {
            return handleInput(charTyped);
        }
    }
    return "";
}
