
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.hpp"
#include "BFS.hpp"

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

            // Custom Start and Goal
            if (const auto* key =
                    event->getIf<sf::Event::KeyPressed>()) {

                if (key->code == sf::Keyboard::Key::S) {
                    placingStart = true;
                    placingGoal = false;

                    std::cout << "Select a new Start cell."
                              << std::endl;
                }

                else if (key->code == sf::Keyboard::Key::G) {
                    placingGoal = true;
                    placingStart = false;

                    std::cout << "Select a new Goal cell."
                              << std::endl;
                }
            }

            // Mouse click
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

                        int index = indexOf(row, col);

                        // Place Start
                        if (placingStart) {

                            if (row != goalRow || col != goalCol) {
                                startRow = row;
                                startCol = col;
                                grid[index].isWall = false;
                            }

                            placingStart = false;
                        }

                        // Place Goal
                        else if (placingGoal) {

                            if (row != startRow || col != startCol) {
                                goalRow = row;
                                goalCol = col;
                                grid[index].isWall = false;
                            }

                            placingGoal = false;
                        }

                        // Toggle wall
                        else {

                            if (row != startRow || col != startCol) {
                                if (row != goalRow || col != goalCol) {
                                    grid[index].isWall =
                                        !grid[index].isWall;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Keyboard input: Space
        bool spaceIsPressed =
            sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::Space
            );

        if (spaceIsPressed && !spaceWasPressed) {
            startBFS();
        }

        spaceWasPressed = spaceIsPressed;

        // Update BFS
        if (isSearching) {
            updateBFS();
        }

        // Animate shortest path
        if (isAnimatingPath) {
            updatePathAnimation();
        }

        // Draw grid
        window.clear(sf::Color(18, 22, 30));

        drawGrid(window);

        window.display();
    }

    return 0;
}
