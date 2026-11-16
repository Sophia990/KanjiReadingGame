#include "Button.h"

void Button::setPosition(sf::Vector2f point) {
    button.setOrigin(button.getLocalBounds().getCenter());
    button.setPosition(point);

    text.setOrigin(text.getLocalBounds().getCenter());
    text.setPosition(point);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(button, states);
    target.draw(text, states);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    const sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    return button.getGlobalBounds().contains(mousePosition);
}