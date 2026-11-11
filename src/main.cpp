#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "FallingWord.h"
#include "WordList.h"
#include "FallingWordList.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "Kanji Reading Game" );

	const float BOTTOM_LINE_Y_COORDINATE = static_cast<float>(window.getSize().y) - 400.f;

	// points and lives
	int points = 0;
	int lives = 5;

	// load font
	sf::Font font;
	if (!font.openFromFile("assets/fonts/NotoSansJP-Black.ttf")) std::cout << "Font not found\n";

	// for words falling on screen
	sf::Clock fallClock;
	const float fallSpeed = 30.f;

	// for spawning words at a time interval
	sf::Clock dropClock;
	const float dropInterval = 2.f;

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

	// make points text
	sf::Text pointsText(font);
	pointsText.setString("Points: " + std::to_string(points));
	pointsText.setCharacterSize(50);
	pointsText.setFillColor(sf::Color::White);
    pointsText.setOrigin({pointsText.getLocalBounds().size.x, 0.f});
    pointsText.setPosition({static_cast<float>(window.getSize().x) - 300.f, static_cast<float>(window.getSize().y) - 300.f});

	// make lives text
	sf::Text livesText(font);
	livesText.setString("Lives: " + std::to_string(lives));
	livesText.setCharacterSize(50);
	livesText.setFillColor(sf::Color::White);
    livesText.setPosition({300.f, static_cast<float>(window.getSize().y) - 300.f});

	// for randomness
	std::random_device rd;
	std::mt19937 randomNumberGenerator(rd());
	std::uniform_real_distribution<float> xDist(100.f, static_cast<float>(window.getSize().x) - 100);

	WordList wordList;
	std::uniform_int_distribution<int> wordDist(0, static_cast<int>(std::size(wordList.tempWordArray)) - 1);

	FallingWordList fallingWordList;

	sf::String currentAnswer = "";

	while ( window.isOpen() )
	{
		float dt = fallClock.restart().asSeconds();

		if (dropClock.getElapsedTime().asSeconds() >= dropInterval) {
			fallingWordList.dropWord(xDist, wordDist, randomNumberGenerator, font, wordList);
			dropClock.restart();
		}

		fallingWordList.update(dt, fallSpeed, BOTTOM_LINE_Y_COORDINATE, currentAnswer, points, lives);
        pointsText.setString("Points: " + std::to_string(points));
        livesText.setString("Lives: " + std::to_string(lives));

		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			if ( event->is<sf::Event::TextEntered>() )
				currentAnswer = answerText.handleTypedOn(*event);
		}

		window.clear();
		answerText.drawTextbox(window);
		window.draw(pointsText);
		window.draw(livesText);
		window.draw(bottomLine.data(), bottomLine.size(), sf::PrimitiveType::Lines);
		for (FallingWord& word : fallingWordList.fallingWordList) {
			word.drawWord(window);
		}
		window.display();
	}
}
