#include "Game.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>

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

    sf::Text makeCentredText(const sf::Font& font,
                             const sf::String& string,
                             sf::Vector2f position,
                             unsigned int size = textSize,
                             sf::Color colour = textColour) {
        sf::Text textToReturn(font);
        textToReturn.setString(string);
        textToReturn.setCharacterSize(size);
        textToReturn.setFillColor(colour);
        textToReturn.setOrigin(textToReturn.getLocalBounds().getCenter());
        textToReturn.setPosition(position);

        return textToReturn;
    }

    sf::Font loadFont(const std::string& path) {
        sf::Font font;
        if (!font.openFromFile(path)) throw std::runtime_error("Failed to load font: " + path);
        return font;
    }

    sf::SoundBuffer loadSoundBuffer(const std::string& path) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path)) std::cerr << "Failed to load sound: " << path << "\n";
        return buffer;
    }
} // namespace

Game::Game()
    : window(sf::VideoMode::getDesktopMode(), "It's Raining Kanji"),
      windowSize(window.getSize()),
      centre(windowSize / 2.f),
      bottomLineYCoordinate(windowSize.y - bottomLineOffset),
      font(loadFont(fontPath)),
      correctBuffer(loadSoundBuffer(correctSoundPath)),
      incorrectBuffer(loadSoundBuffer(incorrectSoundPath)),
      correctSound(correctBuffer),
      incorrectSound(incorrectBuffer),
      randomNumberGenerator(std::random_device{}()),
      xDist(wordXLimitOffset, windowSize.x - wordXLimitOffset),
      answerText(textSize, textColour, font),
      pointsText(font),
      livesText(font),
      titleText(makeCentredText(font, "It's Raining Kanji", {centre.x, centre.y - startMenuOffset}, headingTextSize)),
      startButton("Start", {startButtonWidth, buttonHeight}, buttonTextSize, buttonColour, textColour, font),
      gameOverText(makeCentredText(font, "Game Over!", {centre.x, centre.y - gameOverMenuOffset}, headingTextSize)),
      finalPointsText(
          makeCentredText(font, "Points: " + std::to_string(startingPoints), {centre.x, centre.y}, headingTextSize)),
      returnToMenuButton(
          "Return to Menu", {returnButtonWidth, buttonHeight}, buttonTextSize, buttonColour, textColour, font),
      points(startingPoints),
      lives(startingLives),
      state(State::StartMenu) {
    window.setVerticalSyncEnabled(true);

    // display window first to avoid flash while assets load
    window.clear();
    window.display();

    if (!wordList.readCSV(csvPath)) throw std::runtime_error("Failed to load vocabulary: " + csvPath);
    wordList.reset(randomNumberGenerator);

    if (!music.openFromFile(musicPath)) std::cerr << "Failed to load music: " << musicPath << "\n";
    music.setLooping(true);

    bottomLine = {sf::Vertex{sf::Vector2f(0.f, bottomLineYCoordinate)},
                  sf::Vertex{sf::Vector2f(windowSize.x, bottomLineYCoordinate)}};

    answerText.setPosition({centre.x, windowSize.y - answerTextboxOffset});
    answerText.setLimit(answerTextLimit);

    pointsText.setString("Points: " + std::to_string(points));
    pointsText.setCharacterSize(textSize);
    pointsText.setFillColor(textColour);
    pointsText.setOrigin({pointsText.getLocalBounds().size.x, 0.f});
    pointsText.setPosition({windowSize.x - pointsLivesTextOffset, windowSize.y - pointsLivesTextOffset});

    livesText.setString("Lives: " + std::to_string(lives));
    livesText.setCharacterSize(textSize);
    livesText.setFillColor(textColour);
    livesText.setPosition({pointsLivesTextOffset, windowSize.y - pointsLivesTextOffset});

    startButton.setPosition({centre.x, centre.y + startMenuOffset});
    returnToMenuButton.setPosition({centre.x, centre.y + gameOverMenuOffset});
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();

        switch (state) {
        case State::StartMenu:
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (startButton.isMouseOver(window)) startGame();
            }
            break;

        case State::Playing:
            if (event->is<sf::Event::TextEntered>()) {
                const sf::String answer = answerText.handleTypedOn(*event);
                if (!answer.isEmpty()) {
                    if (const int correct = fallingWordList.submitAnswer(answer); correct > 0) {
                        points += correct;
                        correctSound.play();
                    }
                }
            }
            break;

        case State::GameOver:
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (returnToMenuButton.isMouseOver(window)) resetGame();
            }
            break;
        }
    }
}

void Game::update() {
    if (state != State::Playing) return;

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

    if (lives == 0) {
        state = State::GameOver;
        music.stop();
        finalPointsText.setString("Points: " + std::to_string(points));
        finalPointsText.setOrigin(finalPointsText.getLocalBounds().getCenter());
    }
}

void Game::render() {
    window.clear();

    switch (state) {
    case State::StartMenu:
        window.draw(titleText);
        window.draw(startButton);
        break;

    case State::Playing:
        window.draw(answerText);
        window.draw(pointsText);
        window.draw(livesText);
        window.draw(bottomLine.data(), bottomLine.size(), sf::PrimitiveType::Lines);
        window.draw(fallingWordList);
        break;

    case State::GameOver:
        window.draw(gameOverText);
        window.draw(finalPointsText);
        window.draw(returnToMenuButton);
        break;
    }

    window.display();
}

void Game::startGame() {
    fallClock.restart();
    dropClock.restart();
    music.play();
    state = State::Playing;
}

void Game::resetGame() {
    points = startingPoints;
    lives = startingLives;
    answerText.clearText();
    wordList.reset(randomNumberGenerator);
    fallingWordList.clearWords();
    state = State::StartMenu;
}