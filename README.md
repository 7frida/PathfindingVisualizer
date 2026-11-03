# Pathfinding Visualiser

A C++ application that visualises pathfinding algorithms using a graphical grid interface, built with SFML 3.

## Features

- Interactive grid-based environment
- Click cells to create and remove obstacles
- Fixed start and goal positions
- Breadth-First Search (BFS) pathfinding
- Visual representation of explored cells and the shortest path

## Technologies

- C++17
- SFML 3
- CMake

## Controls

| Input | Action |
|---|---|
| Left mouse button | Toggle a wall |
| Space | Run Breadth-First Search |

## Getting Started

### Requirements

- C++17 compatible compiler
- CMake 3.20 or later
- SFML 3

### Build and Run

```bash
cmake -S . -B build
cmake --build build
./build/pathfinder
```

## Current Progress

This project is currently under development. More features, including animated pathfinding and additional algorithms such as A*, are planned.

## Author

Frida