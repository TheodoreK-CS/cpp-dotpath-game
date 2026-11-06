# 2D Grid Pathfinding & Puzzle Game (C++)

An interactive 2D grid-based pathfinding puzzle game built in **C++** using the **Simple Graphics Library (SGG)** and **OpenGL/SDL2**. The objective is to navigate a continuous path across multi-stage grid topologies to cover all valid nodes without backtracking.

## Tech Stack
* **Language:** C++ (Standard C++14 / MSVC v143)
* **Graphics & Audio:** SGG (Simple Graphics Library), OpenGL, GLEW, SDL2, FreeImage
* **Build System / IDE:** Visual Studio 2022 (`x64`)

## Repository Structure
* `Application/` — Core C++ source code (`.cpp`) and header files (`.h`) implementing the game loop, grid logic, and level states.
* `sgg/` — SGG framework headers and compiled library dependencies.
* `bin/` — Runtime directory containing game assets (textures, fonts, audio), required `.dll` files, and the compiled executable.
* `Application.sln` — Visual Studio Solution file for building and debugging.

## How to Run
### Option 1: Run Pre-compiled Executable (Windows x64)
1. Clone or download this repository.
2. Navigate to the `bin/` directory.
3. Run `Application.exe`.

### Option 2: Build from Source
1. Open `Application.sln` in **Visual Studio 2022**.
2. Set the build configuration to **Release** (or **Debug**) and platform to **x64**.
3. Ensure the project Working Directory is set to `$(SolutionDir)bin` (under *Project Properties -> Debugging -> Working Directory*).
4. Build and run the solution (`F5`).

<img width="1498" height="753" alt="image" src="https://github.com/user-attachments/assets/c7ccff1b-3711-4abb-b6e0-5da2639aea76" />

<img width="1493" height="743" alt="image" src="https://github.com/user-attachments/assets/84714384-59d4-41cc-bcbe-ac7fb02c4756" />


