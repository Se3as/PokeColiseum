## Pokémon Coliseum
A retro-style turn-based Pokémon battle simulator
(Inspired by the original GBC Pokémon Crystal battle system)

## 🕹️ How to Play
To run the game:

Make sure you have a C++ compiler and the FLTK library installed, as well as SFML.

Open a terminal, navigate to the PokeColiseum folder.

Run the following command: ./build.sh

# 🅰️ Font Used (Optional)
This game supports the "Pokemon Classic" font to enhance the retro Game Boy experience.

If the font is not installed, the game will fall back to a default system font (like Helvetica).

# 🎵 Battle Music

This game uses background music inspired by the original Pokémon Crystal battle theme.  
To enable music, make sure you have SFML installed: sudo apt install libsfml-dev

# 🔡 How to enable the Pokémon font:
Download the font from this link:
Pokemon Classic Font – dafont.com

Install it on your system then restart the game.

The game will automatically detect if the font "Pokemon Classic" is available and use it.


## 🎮 Game Controls
Once the game starts, you’ll be taken through a short intro and trainer gender selection.
During battle, you’ll interact with the following classic-style buttons:

FIGHT – Show your Pokémon's 4 available moves.

RUN – Ends the battle.

PKMN – Sends your Pokémon to battle.

When you press FIGHT, four attack moves are shown.
Click on a move to use it against the opponent.
Then click on the emerging window with the attack information to execute the attack.

## ⚔️ Battle Logic
Each Pokémon has HP and a set of attack-only moves.

Moves have a damage value and a type (e.g., Fire, Water).

When a move is used:

The game calculates type effectiveness (e.g., Water vs Fire is 2× damage).

The move’s damage is applied to the opponent’s HP.

The battle ends when either Pokémon’s HP reaches 0.

There are two possible outcomes:

If your Pokémon is defeated:
"Gold is out of usable Pokémon!"

If you win the battle:
"Pokémon Trainer was defeated!"

## 👨‍💻 Authors
Juan Sebastián Loaiza
Sergio Solano
Adrián Arias Vargas

All intellectual property belongs to The Pokémon Company.
(PLEASE DON’T SUE US!)