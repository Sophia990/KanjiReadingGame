#include "Button.h"
#include "FallingWordList.h"
#include "Textbox.h"
#include "WordList.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <random>
#include <string>

namespace {
    constexpr int startingLives = 5;
    constexpr int startingPoints = 0;
    constexpr float baseFallSpeed = 30.f;
    constexpr float speedIncreasePerPoint = 5.f;
    constexpr float dropInterval = 2.f;

    constexpr unsigned int textSize = 50;
    constexpr unsigned int headingTextSize = 200;
    constexpr unsigned int buttonTextSize = 30;

    constexpr sf::Color textColour = sf::Color::White;
    constexpr sf::Color buttonColour = sf::Color::Blue;

    constexpr size_t answerTextLimit = 50;

    constexpr float bottomLineOffset = 400.f;
    constexpr float answerTextboxOffset = 200.f;
    constexpr float pointsLivesTextOffset = 300.f;
    constexpr float wordXLimitOffset = 100.f;
    constexpr float startMenuOffset = 150.f;
    constexpr float gameOverMenuOffset = 300.f;

    constexpr float buttonHeight = 100.f;
    constexpr float startButtonWidth = 200.f;
    constexpr float returnButtonWidth = 300.f;

    const std::string fontPath = "assets/fonts/NotoSansJP-Black.ttf";
    const std::string correctSoundPath = "assets/audio/correct.wav";
    const std::string incorrectSoundPath = "assets/audio/incorrect.wav";
    const std::string musicPath = "assets/audio/music.ogg";
    const std::string csvPath = "assets/vocab/vocab-n5.csv";

    sf::Text makeCentredText(const sf::Font& font, const sf::String& string, sf::Vector2f position, unsigned int size = textSize, sf::Color colour = textColour) {
        sf::Text textToReturn(font);
        textToReturn.setString(string);
        textToReturn.setCharacterSize(size);
        textToReturn.setFillColor(colour);
        textToReturn.setOrigin(textToReturn.getLocalBounds().getCenter());
        textToReturn.setPosition(position);

        return textToReturn;
    }
}

enum class GameState { StartMenu, Playing, GameOver };

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "It's Raining Kanji");

    window.setVerticalSyncEnabled(true);

    // display window first to avoid flash while assets load
    window.clear();
    window.display();

    GameState gameState = GameState::StartMenu;

    const sf::Vector2f windowSize(window.getSize());
    const sf::Vector2f centre = windowSize / 2.f;
    const float bottomLineYCoordinate = windowSize.y - bottomLineOffset;

    // points and lives
    int points = startingPoints;
    int lives = startingLives;

    // load font
    sf::Font font;
    if (!font.openFromFile(fontPath)) {
        std::cerr << "Failed to load font: " << fontPath << "\n";
        return EXIT_FAILURE;
    }

    // for sound effects
    sf::SoundBuffer correctBuffer;
    sf::SoundBuffer incorrectBuffer;
    if (!correctBuffer.loadFromFile(correctSoundPath))
        std::cerr << "Failed to load sound: " << correctSoundPath << "\n";
    if (!incorrectBuffer.loadFromFile(incorrectSoundPath))
        std::cerr << "Failed to load sound: " << incorrectSoundPath << "\n";
    sf::Sound correctSound(correctBuffer);
    sf::Sound incorrectSound(incorrectBuffer);

    // for music
    sf::Music music;
    if (!music.openFromFile(musicPath)) std::cerr << "Failed to load music: " << musicPath << "\n";
    music.setLooping(true);

    // for words falling on screen
    sf::Clock fallClock;

    // for spawning words at a time interval
    sf::Clock dropClock;

    // make textbox for answer
    Textbox answerText(textSize, textColour, font);
    answerText.setPosition(
        {centre.x, windowSize.y - answerTextboxOffset});
    answerText.setLimit(answerTextLimit);

    // make bottom line
    std::array bottomLine = {sf::Vertex{sf::Vector2f(0.f, bottomLineYCoordinate)},
                             sf::Vertex{sf::Vector2f(windowSize.x, bottomLineYCoordinate)}};

    // make points text
    sf::Text pointsText(font);
    pointsText.setString("Points: " + std::to_string(points));
    pointsText.setCharacterSize(textSize);
    pointsText.setFillColor(textColour);
    pointsText.setOrigin({pointsText.getLocalBounds().size.x, 0.f});
    pointsText.setPosition(
        {windowSize.x - pointsLivesTextOffset, windowSize.y - pointsLivesTextOffset});

    // make lives text
    sf::Text livesText(font);
    livesText.setString("Lives: " + std::to_string(lives));
    livesText.setCharacterSize(textSize);
    livesText.setFillColor(textColour);
    livesText.setPosition({pointsLivesTextOffset, windowSize.y - pointsLivesTextOffset});

    // for randomness
    std::random_device rd;
    std::mt19937 randomNumberGenerator(rd());
    std::uniform_real_distribution<float> xDist(wordXLimitOffset, windowSize.x - wordXLimitOffset);

    WordList wordList;
    if (!wordList.readCSV(csvPath)) return EXIT_FAILURE;
    wordList.reset(randomNumberGenerator);

    FallingWordList fallingWordList;

    sf::String currentAnswer;

    // title text
    sf::Text titleText = makeCentredText(font, "It's Raining Kanji", {centre.x, centre.y - startMenuOffset}, headingTextSize);

    // start button
    Button startButton("Start", {startButtonWidth, buttonHeight}, buttonTextSize, buttonColour, textColour, font);
    startButton.setPosition(
        {centre.x, centre.y + startMenuOffset});

    // game over text
    sf::Text gameOverText = makeCentredText(font, "Game Over!", {centre.x, centre.y - gameOverMenuOffset}, headingTextSize);

    // final points text
    sf::Text finalPointsText = makeCentredText(font, "Points: " + std::to_string(points), {centre.x, centre.y}, headingTextSize);

    // return to menu button
    Button returnToMenuButton("Return to Menu", {returnButtonWidth, buttonHeight}, buttonTextSize, buttonColour, textColour, font);
    returnToMenuButton.setPosition(
        {centre.x, centre.y + gameOverMenuOffset});

    auto startGame = [&]() {
        fallClock.restart();
        dropClock.restart();
        music.play();
        gameState = GameState::Playing;
    };

    auto resetGame = [&]() {
        points = startingPoints;
        lives = startingLives;
        answerText.clearText();
        wordList.reset(randomNumberGenerator);
        fallingWordList.clearWords();
        gameState = GameState::StartMenu;
    };

    while (window.isOpen()) {
        while (window.isOpen() && gameState == GameState::StartMenu) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
                if (event->is<sf::Event::MouseButtonPressed>())
                    if (startButton.isMouseOver(window)) startGame();
            }

            window.clear();
            window.draw(titleText);
            window.draw(startButton);
            window.display();
        }

        while (window.isOpen() && lives > 0 && gameState == GameState::Playing) {
            float dt = fallClock.restart().asSeconds();

            if (dropClock.getElapsedTime().asSeconds() >= dropInterval) {
                fallingWordList.dropWord(xDist, randomNumberGenerator, font, wordList);
                dropClock.restart();
            }

            const float currentFallSpeed = baseFallSpeed + static_cast<float>(points) * speedIncreasePerPoint;
            if (const int missed = fallingWordList.update(dt, currentFallSpeed, bottomLineYCoordinate); missed > 0) {
                lives = std::max(0, lives - missed);
                incorrectSound.play();
            }
            pointsText.setString("Points: " + std::to_string(points));
            livesText.setString("Lives: " + std::to_string(lives));

            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
                if (event->is<sf::Event::TextEntered>()) {
                    const sf::String answer = answerText.handleTypedOn(*event);
                    if (!answer.isEmpty()) {
                        if (const int correct = fallingWordList.submitAnswer(answer); correct > 0) {
                            points += correct;
                            correctSound.play();
                        }
                    }
                }
            }

            window.clear();
            window.draw(answerText);
            window.draw(pointsText);
            window.draw(livesText);
            window.draw(bottomLine.data(), bottomLine.size(), sf::PrimitiveType::Lines);
            window.draw(fallingWordList);
            window.display();
        }

        gameState = GameState::GameOver;
        music.stop();

        while (window.isOpen() && gameState == GameState::GameOver) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
                if (event->is<sf::Event::MouseButtonPressed>())
                    if (returnToMenuButton.isMouseOver(window)) resetGame();
            }

            window.clear();
            finalPointsText.setString("Points: " + std::to_string(points));
            finalPointsText.setOrigin(finalPointsText.getLocalBounds().getCenter());
            window.draw(gameOverText);
            window.draw(finalPointsText);
            window.draw(returnToMenuButton);
            window.display();
        }
    }
}
