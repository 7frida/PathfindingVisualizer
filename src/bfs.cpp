
#include "BFS.hpp"
#include "Grid.hpp"

#include <iostream>
#include <algorithm>

// Actual BFS state
std::queue<int> frontier;
std::vector<int> parent(ROWS * COLS, -1);
std::vector<int> path;

bool isSearching = false;
bool isAnimatingPath = false;
bool pathFound = false;

int pathIndex = 0;

// Start BFS
void startBFS() {

    // Reset previous search results
    for (Cell& cell : grid) {
        cell.visited = false;
        cell.isPath = false;
    }

    // Reset BFS data
    frontier = std::queue<int>();
    parent.assign(ROWS * COLS, -1);
    path.clear();

    isSearching = true;
    isAnimatingPath = false;
    pathFound = false;
    pathIndex = 0;

    // Initialise Start cell
    int start = indexOf(startRow, startCol);
    grid[start].visited = true;

    frontier.push(start);
}

// Reconstruct shortest path
void reconstructPath() {

    int start = indexOf(startRow, startCol);
    int goal = indexOf(goalRow, goalCol);

    int current = goal;

    // Follow parent pointers backwards
    while (current != start) {
        path.push_back(current);
        current = parent[current];
    }

    // Include Start
    path.push_back(start);

    // Reverse to get Start -> Goal
    std::reverse(path.begin(), path.end());

    // Prepare path animation
    pathIndex = 0;
    isAnimatingPath = true;
}

// Update BFS one cell at a time
void updateBFS() {

    if (!isSearching) {
        return;
    }

    // No cells left to explore
    if (frontier.empty()) {
        isSearching = false;
        pathFound = false;
        std::cout << "No path found!" << std::endl;
        return;
    }

    // Get next cell
    int current = frontier.front();
    frontier.pop();

    int goal = indexOf(goalRow, goalCol);

    // Goal reached
    if (current == goal) {
        isSearching = false;
        pathFound = true;

        reconstructPath();

        std::cout << "Goal reached!" << std::endl;
        return;
    }

    // Convert index to row and column
    int row = current / COLS;
    int col = current % COLS;

    // Four movement directions
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

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

        // Mark visited
        grid[neighbour].visited = true;

        // Record parent
        parent[neighbour] = current;

        // Add to queue
        frontier.push(neighbour);
    }
}

// Animate shortest path
void updatePathAnimation() {

    if (pathIndex >= static_cast<int>(path.size())) {
        isAnimatingPath = false;
        return;
    }

    int current = path[pathIndex];

    grid[current].isPath = true;

    pathIndex++;
}
