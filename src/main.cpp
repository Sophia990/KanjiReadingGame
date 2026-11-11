#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "FallingWord.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "Kanji Reading Game" );

	const float BOTTOM_LINE_Y_COORDINATE = static_cast<float>(window.getSize().y) - 400.f;

	// load font
	sf::Font font;
	if (!font.openFromFile("assets/fonts/NotoSansJP-Black.ttf")) std::cout << "Font not found\n";

	// for words falling on screen
	sf::Clock clock;
	const float fallSpeed = 30.f;

    // make textbox for answer
	Textbox answerText(50, sf::Color::White, font);
	answerText.setPosition({(static_cast<float>(window.getSize().x) / 2.f),
							static_cast<float>(window.getSize().y) - 200.f});
	answerText.setLimit(50);

	// make bottom line
	std::array bottomLine = {
			sf::Vertex{sf::Vector2f(0.f, BOTTOM_LINE_Y_COORDINATE)},
			sf::Vertex{sf::Vector2f(static_cast<float>(window.getSize().x), BOTTOM_LINE_Y_COORDINATE)}
	};

	// for randomness
	std::random_device rd;
	std::mt19937 randomNumberGenerator(rd());
	std::uniform_real_distribution<float> xDist(100.f, static_cast<float>(window.getSize().x) - 100);

	// temporarily make word to test drawing a word
	sf::Vector2f position = {xDist(randomNumberGenerator), 0.f};
	FallingWord testWord(U"漢字", U"かんじ", U"kanji", font, position);

	while ( window.isOpen() )
	{
		float dt = clock.restart().asSeconds();
		testWord.fall(dt, fallSpeed, BOTTOM_LINE_Y_COORDINATE);

		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			if ( event->is<sf::Event::TextEntered>() )
				answerText.handleTypedOn(*event);
		}

		window.clear();
		answerText.drawTextbox(window);
		window.draw(bottomLine.data(), bottomLine.size(), sf::PrimitiveType::Lines);
		testWord.drawWord(window);
		window.display();
	}
}
