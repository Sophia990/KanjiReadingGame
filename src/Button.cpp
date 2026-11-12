#include "Button.h"

void Button::setBackgroundColour(sf::Color colour) {
    button.setFillColor(colour);
}

void Button::setTextColour(sf::Color colour) {
    text.setFillColor(colour);
}

void Button::setPosition(sf::Vector2f point) {
    button.setOrigin(button.getLocalBounds().getCenter());
    button.setPosition(point);

    text.setOrigin(text.getLocalBounds().getCenter());
    text.setPosition(point);
}

void Button::drawButton(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    return button.getGlobalBounds().contains({static_cast<float>(mouseX), static_cast<float>(mouseY)});
}