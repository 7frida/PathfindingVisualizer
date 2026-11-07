
#include "Grid.hpp"

// Actual grid data
std::vector<Cell> grid(ROWS * COLS);

// Start and Goal positions
int startRow = 0;
int startCol = 0;

int goalRow = ROWS - 1;
int goalCol = COLS - 1;

// Placement modes
bool placingStart = false;
bool placingGoal = false;

// Convert 2D coordinates to 1D index
int indexOf(int row, int col) {
    return row * COLS + col;
}

// Draw the grid
void drawGrid(sf::RenderWindow& window) {

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {

            int index = indexOf(row, col);

            sf::RectangleShape cell(
                sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)
            );

            cell.setPosition(sf::Vector2f(
                OFFSET_X + col * CELL_SIZE,
                OFFSET_Y + row * CELL_SIZE
            ));

            // Start cell
            if (row == startRow && col == startCol) {
                cell.setFillColor(sf::Color(50, 200, 100));
            }

            // Goal cell
            else if (row == goalRow && col == goalCol) {
                cell.setFillColor(sf::Color(230, 70, 70));
            }

            // Wall
            else if (grid[index].isWall) {
                cell.setFillColor(sf::Color(35, 40, 50));
            }

            // Shortest path
            else if (grid[index].isPath) {
                cell.setFillColor(sf::Color(255, 220, 50));
            }

            // Visited cell
            else if (grid[index].visited) {
                cell.setFillColor(sf::Color(100, 180, 230));
            }

            // Empty cell
            else {
                cell.setFillColor(sf::Color(100, 110, 130));
            }

            window.draw(cell);
        }
    }
}
