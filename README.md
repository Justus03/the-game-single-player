## The Game - Single Player Edition

**The Game - Single Player Edition** is a minimalistic, single-player adaptation of the popular cooperative card game "The Game," designed by Steffen Benndorf. This version is implemented in C using the SDL2 and SDL2_ttf libraries, providing a lightweight and engaging experience for fans of the original game.

### Features
- **Single-Player Mode**: Enjoy the strategic challenge of "The Game" in a solo format.
- **Minimalistic Design**: Simple and clean interface for focused gameplay.
- **Randomized Deck**: Each game offers a new challenge with a shuffled deck of cards.
- **Intuitive Controls**: Easy-to-use controls for a seamless gaming experience.
- **Text Rendering**: Utilizes SDL2_ttf for clear and crisp text display.

### How to Play
- **Objective**: Play all the cards from the deck onto four piles according to specific rules.
- **Ascending Piles**: Place cards in increasing order.
- **Descending Piles**: Place cards in decreasing order.
- **Special Rule**: Play a card exactly 10 higher or 10 lower to reset the pile.
- **End of Game**: The game ends when no more valid moves can be made.

### Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/the-game-single-player.git
   ```
2. Install SDL2 and SDL2_ttf libraries. You can find the installation instructions on the [SDL2 website](https://www.libsdl.org/download-2.0.php) and the [SDL2_ttf website](https://www.libsdl.org/projects/SDL_ttf/).
3. Navigate to the project directory:
   ```sh
   cd the-game-single-player
   ```
4. Compile the project:
   ```sh
   gcc -o thegame main.c -lSDL2 -lSDL2_ttf
   ```
5. Run the game:
   ```sh
   ./thegame
   ```

### Requirements
- **C Compiler**: Compatible with GCC or Clang.
- **SDL2 Library**: Ensure SDL2 is installed on your system.
- **SDL2_ttf Library**: Ensure SDL2_ttf is installed on your system.

### To-Do
- Configure a build system (Makefile, CMake, etc.).
- Improve the user interface and graphics.
- Add sound effects and music.
- Implement additional game modes and features.

### Contributing
Feel free to fork the repository and submit pull requests. Contributions, bug reports, and feature requests are welcome!

### License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Enjoy playing "The Game" solo and challenge yourself to achieve the perfect game!
