#include "Textbox.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

sf::String Textbox::getText() {
    return text;
}

void Textbox::handleInput(std::uint32_t unicodeTyped) {
    if (unicodeTyped == DELETE_KEY) {
        if (!text.isEmpty()) {
            text.erase(text.getSize() - 1);
        }
    }
    else if (unicodeTyped == ENTER_KEY) {
        text = "";
    }
    else if (unicodeTyped != ESCAPE_KEY) {
        text += static_cast<char32_t>(unicodeTyped);
    }
    textbox.setString(text + "_");
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

void Textbox::handleTypedOn(const sf::Event& input) {
    if (const auto* textEntered = input.getIf<sf::Event::TextEntered>()) {
        int charTyped = static_cast<int>(textEntered->unicode);
        if (text.getSize() <= limit || charTyped == DELETE_KEY || charTyped == ENTER_KEY) {
            handleInput(charTyped);
        }
    }
}
