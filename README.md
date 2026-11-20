# It's Raining Kanji

Download and play game: https://sophia990.itch.io/its-raining-kanji

*It’s Raining Kanji* is a quiz game in which Japanese learners can test their knowledge of kanji readings for JLPT N5 (beginner) level vocabulary, by typing in the readings for words as they fall down from the top of the screen, similarly to the alien invaders in *Space Invaders*. Letting a word reach the bottom of the screen costs you a life, and the aim is to enter as many correct answers as you can before you run out of lives. The more answers you get correct, the faster the words fall, meaning the game gets more challenging the better you are.

For this game, I wanted to create something aligning with my personal interests outside of games, in this case, learning Japanese, as well as have a project I could show off using C++ outside of a game engine.

## Tech Stack
- Language: C++17
- Library: SFML 3.1.0 (Graphics, Audio)
- Build: CMake 3.28+ (FetchContent for SFML)
- Assets: Noto Sans JP Black; CSV vocabulary; audio

## Controls
- Press Start to begin
- Type readings in kana or romaji (hiragana for most readings; use katakana if the word also contains katakana)
- Enter to submit
- Backspace deletes the last character; Delete clears the textbox
- A life is lost when a word reaches the bottom line; the game ends at zero lives
- Return to Menu resets and lets you play again

## Requirements
- CMake, version 3.28 or higher
- A C++17 compiler
- Git
- Initial configuration requires a network connection to download SFML 3.1.0 from GitHub

## Instructions to Build and Run
1. `cmake -B build`
2. `cmake --build build --config Release`
3. Then run `build/bin/ItsRainingKanji` or `build/bin/Release/ItsRainingKanji`

## Gameplay
*It’s Raining Kanji* begins with a start menu, and loops through a start menu, to game, to game over screen, to returning to the start menu loop. Vocabulary containing kanji falls from the top of the screen, and the player must type in the correct reading before it reaches the bottom of the screen, or lose a life. The game will accept inputs in kana (Japanese phonetic syllabaries) or romaji (transliterations into the Latin alphabet), so that the player can use whichever input system is most comfortable to them, and would not need to set up a Japanese keyboard if they have not done so already.

When the player enters a correct answer, they earn a point. They will eventually be shown their final score at the end of the game, when they run out of lives. The more points the player has, the faster the vocabulary falls. This increases the challenge over time, in line with the player’s skill, making what is essentially kanji reading drills into a fun and engaging game.

## Implementation

### Architecture
The main game loops and logic for rendering the window, as well as the necessary constants, exist in a `Game` class. This class keeps track of the game’s state (`StartMenu`, `Playing`, or `GameOver`), which controls what events are being listened for and what is drawn on the window. Starting the game, losing the game or returning to the menu triggers a change in the game state. Additionally, logic in the `Game` class controls, for example, words being dropped from the top of the screen at a specific interval, sounds playing, and UI text changing.

The main function instantiates the `Game` object, which is non-copyable since it owns various SFML resources, and calls `run()` on it. It also catches any exceptions `run()` throws and ends the game if this happens.

Other classes include `Word` and `WordList`. `WordList` contains two vectors of `Word` objects; one of these holds the vocabulary read directly from the CSV file, and the other is shuffled and has vocabulary taken from it to be dropped across the screen.

The game also has `FallingWord`, which inherits from `Word`, and `FallingWordList` classes. `FallingWord` expands upon `Word` by containing members that allow the word to be displayed and fall across the screen. `FallingWordList` contains a list of the `FallingWord` objects currently being shown on the screen.

Finally, there are two UI classes, `Textbox` and `Button`, to contain logic for objects of these types and, in the case of buttons, allow multiple buttons to be easily added to the game.

`FallingWord`, `FallingWordList`, `Textbox` and `Button` all inherit from SFML’s `Drawable` class, as they are displayed on the screen.

### File Handling
Vocabulary is loaded from a CSV file containing the kanji, kana reading and romaji reading, and put into a vector of `Word` objects. Because I downloaded a pre-made vocabulary list, rather than make my own, the CSV file contains vocabulary that does not contain kanji, and has kana in its place in the column. Therefore, the code filters these out when reading the file by checking if the kanji value is equal to the kana reading value. One particular challenge was handling the unicode characters to preserve the correct Japanese, which I did using `sf::String::fromUtf8`.

This vector is then copied into a `remainingWords` vector, which is then shuffled. The function `takeWord()` is used to pop a new word from the back, and returns `std::optional` in case the vector is empty, although no player should be able to reach this point.

### Answer Matching
When accepting answers, as I mentioned above, the code accepts either kana or romaji answers. It also converts all ASCII characters entered in the answer to lowercase, while not touching kana, so that romaji answers are case-insensitive. In the case that there are two kanji words falling with the same reading at the same time, entering this reading correctly will clear both words and give the player a point for each of these words.

### Text Input
I programmed the answer textbox to handle unicode input in Japanese, in the font Noto Sans JP Black, as well as handle various special keys. The backspace key deletes a character, but the delete key will also clear the text. Enter submits the answer and clears the text. Other ASCII keys below 0x20 are ignored, and there is a 50-character limit to prevent the answer from stretching over the bounds of the screen.

The code prints a trailing underscore at all times to give the player an indication that this is where text will be printed next. The text also stays centred, as the code resets its origin each time something is typed.

## Future Improvements
Although I am pleased with the result of this project, had I had more time to spend on it, there are various other features I would have implemented. The most significant of these would be to show the player the correct answer to kanji readings they let drop to the bottom of the screen, as this would improve the game’s educational value.

Some other features would be to have other JLPT levels of vocabulary, and to find or make a list of vocabulary more accurate to each level. I would also like to have difficulty levels, allowing the user to choose how many lives they have or the rate at which the fall speed increases. Along the same line, at the moment a player could, in theory, empty the deck of words, although this is not realistically possible due to the increase in fall speed. If this were to happen, the game carries on without ending; it would be safer to show a win screen, or the game over screen, at this point.

Moreover, it would be ideal to have a pause and settings screen. With more time, I would also prioritise unit tests, and add integration and end-to-end tests as well.

## Credits
Music - Tallbeard Studios (https://tallbeard.itch.io/three-red-hearts-prepare-to-dev)

Point earned sound - Mudkip2016 (https://freesound.org/people/Mudkip2016/sounds/423930/)

Life lost sound - AceOfSpadesProduc100 (https://freesound.org/people/AceOfSpadesProduc100/sounds/333785/)

Font - Noto Sans Japanese (https://fonts.google.com/noto/specimen/Noto+Sans+JP)

Vocabulary list - OpenJLPT contributors, & Clan, E. (2026). OpenJLPT: an open JLPT N5–N1 dataset of vocabulary, kanji and grammar (Version 0.3.0) [Data set]. (https://github.com/evanclan/OpenJLPT)
