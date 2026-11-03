
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue> //FIFO
#include <iostream>

// Grid configuration
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
const int GOAL_COL = COLS - 1; //C++ indexing starts at 0

// Cell data
struct Cell {
    bool isWall = false;
    bool visited = false;
    bool isPath = false;
};

// Grid contains 20 x 30 = 600 cells
std::vector<Cell> grid(ROWS * COLS);

// Convert row and column into a single index 
//- Instead of storing the grid as a two-dimensional array, we're storing it in a one-dimensional vector
// simple storage, easy iteration,
int indexOf(int row, int col) {
    return row * COLS + col;
}

// Draw the entire grid
void drawGrid(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(
        sf::Vector2f(
            CELL_SIZE - 2.f,
            CELL_SIZE - 2.f
        )
    );

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {

            int index = indexOf(row, col);

            // Position of this cell
            rectangle.setPosition({
                OFFSET_X + col * CELL_SIZE,
                OFFSET_Y + row * CELL_SIZE
            });

            // Choose cell colour
            if (row == START_ROW && col == START_COL) {
                rectangle.setFillColor(sf::Color(50, 200, 100)); // Green
            }
            else if (row == GOAL_ROW && col == GOAL_COL) {
                rectangle.setFillColor(sf::Color(230, 70, 70)); // Red
            }
            else if (grid[index].isWall) {
                rectangle.setFillColor(sf::Color(35, 40, 50)); // Wall
            }
            else if (grid[index].isPath) {
                rectangle.setFillColor(sf::Color(255, 220, 50)); //Yellow - shortest path
            }
            else if (grid[index].visited) {
                rectangle.setFillColor(sf::Color(100, 180, 230)); //B lue
            }
            else {
                rectangle.setFillColor(sf::Color(100, 110, 130)); // Empty
            }


            window.draw(rectangle);
        }
    }
}

// Breadth-First Search
bool findPath() {

    // Clear previous search results
    for (auto& cell : grid) {
        cell.visited = false;
        cell.isPath = false;
    }

    // Store the parent of each cell
    std::vector<int> parent(ROWS * COLS, -1);

    // Create BFS queue
    std::queue<int> frontier;

    // Start and Goal indices
    int start = indexOf(START_ROW, START_COL);
    int goal = indexOf(GOAL_ROW, GOAL_COL);

    // Begin BFS
    grid[start].visited = true;
    frontier.push(start);

    // Four possible movement directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!frontier.empty()) {

        int current = frontier.front();
        frontier.pop();

        // Have we reached the Goal?
        if (current == goal) {
            break;
        }

        int row = current / COLS;
        int col = current % COLS;

        // Explore neighbours
        for (int i = 0; i < 4; i++) {

            int newRow = row + dr[i];
            int newCol = col + dc[i];

            // Check boundaries
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

            // Mark neighbour as visited
            grid[neighbour].visited = true;

            // Remember where we came from when trace backwards - reconstruct the shortest path
            parent[neighbour] = current;

            // Add neighbour to queue
            frontier.push(neighbour);
        }
    }

    // No path found
    if (!grid[goal].visited) {
        return false;
    }

    // Reconstruct path from Goal to Start
    int current = goal;

    while (current != start) {

        grid[current].isPath = true;

        current = parent[current];
    }

    return true;
}

int main() {

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pathfinding Visualiser"
    );

    window.setFramerateLimit(60);

    bool spaceWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    if (spaceIsPressed && !spaceWasPressed) {
    bool success = findPath();

    if (success) {
        std::cout << "Path found!" << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
}

    spaceWasPressed = spaceIsPressed;

    while (window.isOpen()) {

        while (const auto event = window.pollEvent()) {

    if (event->is<sf::Event::Closed>()) {
        window.close();
    }

    if (const auto* mousePressed =
        event->getIf<sf::Event::MouseButtonPressed>()) {

        if (mousePressed->button == sf::Mouse::Button::Left) {

            // Get mouse position
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            //convert to grid coordinates
            int col = (mousePosition.x - OFFSET_X) / CELL_SIZE;
            int row = (mousePosition.y - OFFSET_Y) / CELL_SIZE;

            if (row >= 0 && row < ROWS &&
                col >= 0 && col < COLS) {

                // Prevent walls on Start or Goal
                if (!((row == START_ROW && col == START_COL) ||
                    (row == GOAL_ROW && col == GOAL_COL))) {

                    int index = indexOf(row, col);
                    grid[index].isWall = !grid[index].isWall; // every click switches
                }
            }
        }
        if (const auto* keyPressed =
            event->getIf<sf::Event::KeyPressed>()) {


        }
        }
    }

        window.clear(sf::Color(18, 22, 30));
        drawGrid(window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

    bool success = findPath();

    if (success) {
        std::cout << "Path found!" << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
}
        window.display();
    }

    return 0;
}
