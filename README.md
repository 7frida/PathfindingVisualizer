# Pathfinding Visualiser

A C++ pathfinding visualiser built with **SFML 3**, allowing users to interact with a grid, place obstacles, customise Start and Goal positions, and watch Breadth-First Search (BFS) explore the grid and find the shortest path.

## Features

### Grid Interaction
- 20 × 30 interactive grid.
- Click cells to add or remove walls.
- Customisable Start and Goal positions.
- Press `S` to enter Start placement mode.
- Press `G` to enter Goal placement mode.
- Prevents Start and Goal from occupying the same cell.
- Automatically removes a wall when placing Start or Goal on that cell.

### Pathfinding
- Breadth-First Search (BFS) implementation.
- Animated exploration of visited cells.
- Parent tracking to reconstruct the shortest path.
- Animated shortest-path visualisation.
- Handles situations where no valid path exists.

## Technologies

- **Language:** C++17
- **Graphics:** SFML 3
- **Build system:** CMake
- **Development environment:** Visual Studio Code

## Getting Started

### Prerequisites

- C++ compiler with C++17 support
- CMake 3.20 or later
- SFML 3

On macOS, you can install the dependencies using Homebrew:

```bash
brew install cmake sfml
```

### Build and Run

Clone the repository:

```bash
gh repo clone 7frida/PathfindingVisualizer
cd PathfindingVisualizer
```

Create a build directory:

```bash
mkdir build
cd build
```

Configure the project:

```bash
cmake ..
```

Build the application:

```bash
cmake --build .
```

Run the visualiser:

```bash
./pathfinder
```

## Controls

| Input | Action |
|---|---|
| `S` | Enter Start placement mode |
| `G` | Enter Goal placement mode |
| Left mouse click | Move Start/Goal or toggle a wall |
| `Space` | Start BFS |

## Colour Legend

| Colour | Meaning |
|---|---|
| Green | Start cell |
| Red | Goal cell |
| Dark grey | Wall |
| Blue | Visited cell |
| Yellow | Shortest path |
| Light grey | Unvisited cell |

## Project Structure

```text
PathfindingVisualizer/
├── src/
│   └── main.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Future Development

- Dijkstra's Algorithm
- A* Search Algorithm
- Weighted terrain and movement costs
- Algorithm selection
- Reset and clear functionality
- Animation speed controls
- Performance comparison between algorithms

## Author

Frida Fengyu Liu