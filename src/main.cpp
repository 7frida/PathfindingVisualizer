
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

// Grid settings
const int ROWS = 20;
const int COLS = 30;
const int CELL_SIZE = 28;

const float OFFSET_X = 20;
const float OFFSET_Y = 80;

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 680;

// Start and Goal positions
const int START_ROW = 0;
const int START_COL = 0;

const int GOAL_ROW = ROWS - 1;
const int GOAL_COL = COLS - 1;

// Cell structure
struct Cell {
    bool isWall = false;
    bool visited = false;
    bool isPath = false;
};

// Grid stored as a 1D vector
std::vector<Cell> grid(ROWS * COLS);

// Convert 2D coordinates to 1D index
int indexOf(int row, int col) {
    return row * COLS + col;
}

// BFS state
std::queue<int> frontier; // next cell
std::vector<int> parent(ROWS * COLS, -1); // predecessor
// std::vector<int> vectorName(numberOfElements, initialValue);
// memory structure that remembers how BFS reached every cell, allowing to recover the shortest route after the search finishes
std::vector<int> path;

bool isSearching = false;
bool isAnimatingPath = false;
bool pathFound = false;

int pathIndex = 0;

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
            if (row == START_ROW && col == START_COL) {
                cell.setFillColor(sf::Color(50, 200, 100));
            }

            // Goal cell
            else if (row == GOAL_ROW && col == GOAL_COL) {
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

// Breadth-First Search
bool findPath() {

    // Reset previous search results
    for (Cell& cell : grid) {
        cell.visited = false;
        cell.isPath = false;
    }

    std::vector<int> parent(ROWS * COLS, -1);
    std::queue<int> frontier;

    int start = indexOf(START_ROW, START_COL);
    int goal = indexOf(GOAL_ROW, GOAL_COL);

    grid[start].visited = true;
    frontier.push(start);

    // Four movement directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // BFS exploration
    while (!frontier.empty()) {

        int current = frontier.front();
        frontier.pop();

        if (current == goal) {
            break;
        }

        int row = current / COLS;
        int col = current % COLS;

        for (int direction = 0; direction < 4; direction++) {

            int newRow = row + dr[direction];
            int newCol = col + dc[direction];

            // Check grid boundaries
            if (newRow < 0 || newRow >= ROWS ||
                newCol < 0 || newCol >= COLS) {
                continue;
            }

            int neighbour = indexOf(newRow, newCol);

            // Skip walls and visited cells
            if (grid[neighbour].isWall ||
                grid[neighbour].visited) {
                continue;
            }

            grid[neighbour].visited = true;
            parent[neighbour] = current;
            frontier.push(neighbour);
        }
    }

    // No path found
    if (!grid[goal].visited) {
        return false;
    }

    // Reconstruct shortest path
    int current = goal;

    while (current != start) {
        grid[current].isPath = true;
        current = parent[current];
    }

    return true;
}

void reconstructPath() {

    int start = indexOf(START_ROW, START_COL);
    int goal = indexOf(GOAL_ROW, GOAL_COL);

    // Start from the Goal
    int current = goal;

    // Follow parent pointers backwards
    while (current != start) {

        path.push_back(current);

        current = parent[current]; //find the parent index untill reach Start
    }

    // Include the Start cell
    path.push_back(start);

    // Reverse the vector path to get Start -> Goal
    std::reverse(path.begin(), path.end());

    // Prepare the path animation
    pathIndex = 0;
    isAnimatingPath = true;
}


void updatePathAnimation() {

    // Stop when every path cell has been animated
    if (pathIndex >= static_cast<int>(path.size())) { //convert type to int - check size
        isAnimatingPath = false;
        return;
    }

    // Get the next cell in the shortest path
    int current = path[pathIndex];

    // Mark it as part of the path
    grid[current].isPath = true;

    // Move to the next path cell
    pathIndex++;
}


void startBFS() {

    // Reset previous search results
    for (Cell& cell : grid) { // & means reference
        cell.visited = false;
        cell.isPath = false;
    }

    // Reset BFS data - parent needs to be cleared every time we start a new BFS
    frontier = std::queue<int>();
    parent.assign(ROWS * COLS, -1); // set to -1
    path.clear();

    isSearching = true;
    isAnimatingPath = false;
    pathFound = false;
    pathIndex = 0;

    // Initialise Start cell
    int start = indexOf(START_ROW, START_COL);
    grid[start].visited = true;

    frontier.push(start);
}


void updateBFS() {

    // Stop if BFS is not running
    if (!isSearching) {
        return;
    }

    // Check whether there are any cells left to explore
    if (frontier.empty()) {
        isSearching = false;
        pathFound = false;
        std::cout << "No path found!" << std::endl;
        return;
    }

    // Get the next cell from the queue
    int current = frontier.front();
    frontier.pop();

    // Check whether we have reached the Goal
    int goal = indexOf(GOAL_ROW, GOAL_COL);

    if (current == goal) {

        isSearching = false;
        pathFound = true;

        reconstructPath(); // shortest path

        std::cout << "Goal reached!" << std::endl;
        return;
    }

    // Convert the current index into row and column
    int row = current / COLS;
    int col = current % COLS;

    // Four possible movement directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Explore the four neighbours
    for (int i = 0; i < 4; i++) {

        int newRow = row + dr[i];
        int newCol = col + dc[i];

        // Check grid boundaries
        if (newRow < 0 || newRow >= ROWS ||
            newCol < 0 || newCol >= COLS) {
            continue;
        }

        int neighbour = indexOf(newRow, newCol);

        // Skip walls and already visited cells
        if (grid[neighbour].isWall ||
            grid[neighbour].visited) {
            continue; //skips the rest of the current loop iteration and moves to the next neighbour
        }

        // Mark as visited
        grid[neighbour].visited = true;

        // Remember where this cell came from
        parent[neighbour] = current;

        // Add it to the BFS queue
        frontier.push(neighbour);
    }
}




int main() {

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pathfinding Visualiser"
    );

    // Detect a new Space press
    bool spaceWasPressed = false;

    // Main game loop
    while (window.isOpen()) {

        // Handle events
        while (const auto event = window.pollEvent()) {

            // Close window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Mouse click to toggle walls
            if (const auto* mousePressed =
                event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mousePressed->button == sf::Mouse::Button::Left) {

                    sf::Vector2i mousePosition =
                        sf::Mouse::getPosition(window);

                    int col =
                        (mousePosition.x - OFFSET_X) / CELL_SIZE;

                    int row =
                        (mousePosition.y - OFFSET_Y) / CELL_SIZE;

                    // Check grid boundaries
                    if (row >= 0 && row < ROWS &&
                        col >= 0 && col < COLS) {

                        // Protect Start and Goal
                        if (!((row == START_ROW && col == START_COL) ||
                              (row == GOAL_ROW && col == GOAL_COL))) {

                            int index = indexOf(row, col);

                            grid[index].isWall =
                                !grid[index].isWall;
                        }
                    }
                }
            }
        }

        // Keyboard input: Space
        bool spaceIsPressed =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

        if (spaceIsPressed && !spaceWasPressed) {
            startBFS();
        }

        spaceWasPressed = spaceIsPressed;

        // Update BFS every frame while searching
        if (isSearching) {
            updateBFS();
        }
        // Animate the shortest path
        if (isAnimatingPath) {
            updatePathAnimation();
        }

        // Draw updated grid
        window.clear(sf::Color(18, 22, 30));

        drawGrid(window);

        window.display();
    }

    return 0;
}
