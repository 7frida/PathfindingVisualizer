
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// Grid settings
inline constexpr int ROWS = 20;
inline constexpr int COLS = 30;
inline constexpr int CELL_SIZE = 28;

inline constexpr float OFFSET_X = 20;
inline constexpr float OFFSET_Y = 80;

inline constexpr int WINDOW_WIDTH = 900;
inline constexpr int WINDOW_HEIGHT = 680;

// Cell structure
struct Cell {
    bool isWall = false;
    bool visited = false;
    bool isPath = false;
};

// Shared variable grid
extern std::vector<Cell> grid;

// Custom Start and Goal positions
extern int startRow;
extern int startCol;
extern int goalRow;
extern int goalCol;

// Placement modes
extern bool placingStart;
extern bool placingGoal;

// Convert 2D coordinates to 1D index
int indexOf(int row, int col);

// Draw the grid
void drawGrid(sf::RenderWindow& window);
