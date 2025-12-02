# Breakout Game (Qt / C++) 🎮

**Breakout** is a classic arcade game developed in C++ using the Qt 6 framework.
This project was created as coursework to demonstrate Object-Oriented Programming (OOP) principles, 2D graphics rendering, and event-driven architecture.

## Game Screenshot
<img width="795" height="596" alt="image" src="https://github.com/user-attachments/assets/399cb15f-1cdb-42a5-9640-685a67afcdb5" />
<img width="800" height="595" alt="image" src="https://github.com/user-attachments/assets/5296d7a8-cf6e-4581-a3d1-65b0350231b1" />
<img width="798" height="596" alt="image" src="https://github.com/user-attachments/assets/5f4a5035-0f94-4df4-b4a5-c1f1120ff834" />
<img width="799" height="598" alt="image" src="https://github.com/user-attachments/assets/af1f0534-670e-4d64-9512-20c11a34cc93" />

## 🚀 Key Features

* **Classic Gameplay:** Paddle control, ball mechanics, and brick destruction.
* **Physics Engine:** Implemented mathematical model for ball reflection off walls and obstacles.
* **Interactive Menu:** Custom UI buttons ("Play Again", "Quit") rendered directly on the graphics scene.
* **Game States:**
    * Countdown before start (3... 2... 1... GO!).
    * Victory screen (when all bricks are destroyed).
    * Game Over screen (when the ball drops).
* **Restart System:** Ability to restart the game seamlessly without relaunching the application (full scene and memory cleanup).

## 🛠️ Tech Stack

* **Language:** C++17
* **Framework:** Qt 6.x
* **Architecture:** Qt Graphics View Framework (`QGraphicsScene`, `QGraphicsView`, `QGraphicsItem`)
* **Patterns:** Signals & Slots, Game Loop (via `QTimer`).

## 📂 Project Structure

The project is built on OOP principles, where each game element is a separate class:

* **`Game`** (inherits `QGraphicsView`): The main controller class. Handles scene initialization, timers, level logic, and state switching (Menu/Game).
* **`Ball`** (inherits `QObject`, `QGraphicsRectItem`): Implements movement physics, collision detection (AABB), and reflection logic.
* **`Paddle`** (inherits `QGraphicsRectItem`): Handles keyboard input (`keyPressEvent`) for player control.
* **`Brick`** (inherits `QGraphicsRectItem`): Static objects forming the level layout.
* **`Button`** (inherits `QObject`, `QGraphicsRectItem`): Custom UI element for mouse interaction.

## 🎮 How to Play

1.  Launch the game.
2.  Wait for the countdown to finish.
3.  Use the **LEFT** (⬅️) and **RIGHT** (➡️) arrow keys to move the paddle.
4.  Your goal is to break all the bricks and prevent the ball from falling below the bottom edge of the screen.

---
**Author:** [Ivanchenko Oleg(MrScarletello)]
**Year:** 2025
