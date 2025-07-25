# 🌲 Timber!!! – SFML C++ Game 🎮

Welcome to **Timber!!!**, a classic arcade-style wood-chopping game built with **C++** and **SFML (Simple and Fast Multimedia Library)**. Get ready to chop trees, dodge falling branches, and beat the clock! 🪓⏳

---

## 📌 Features

- 🎮 **Real-time gameplay** with responsive keyboard controls
- 🌤️ Dynamic clouds and buzzing bees for atmospheric motion
- 🪵 Flying log effect and axe animations
- 🧠 Branch spawning algorithm with random left/right logic
- 🎵 Sound effects for chopping, death, and timeout
- ⏰ Time bar that shrinks with time pressure
- 💀 Game over conditions (squished or timeout)
- 🔁 Restart capability with "Enter" key

---

## 🛠️ Tech Stack

| Technology | Description |
|------------|-------------|
| **C++** | Core game logic |
| **SFML** | Graphics, audio, input handling |
| **G++ / Clang++** | Compilation |
| **Makefile** *(optional)* | Automation |


---

## 🎮 Controls

| Key        | Action             |
|------------|--------------------|
| `Enter`    | Start / Restart game |
| `Left`     | Chop on left side   |
| `Right`    | Chop on right side  |
| `Escape`   | Exit the game       |

---

## 🔧 How to Build and Run

### 📁 Prerequisites
- C++ compiler (e.g., `g++`)
- [SFML 2.5+](https://www.sfml-dev.org/download.php)

### 🖥️ Compile via Terminal

```bash
g++ -std=c++17 main.cpp -o Timber -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./Timber
