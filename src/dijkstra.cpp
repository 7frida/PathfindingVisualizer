// dijkstra: movement costs
// priority_queue: prioritise the cheapest available cell


#include "Dijkstra.hpp"
#include "Grid.hpp"

#include <iostream>
#include <algorithm>
#include <limits>

std::priority_queue<
    std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>
> pq;  //priority queue-storing pairs of {distance, cellIndex}

std::vector<int> distanceCost(ROWS * COLS); //cheapest known cost to reach each cell
std::vector<int> dijkstraParent(ROWS * COLS, -1);
std::vector<int> dijkstraPath;

bool isDijkstraSearching = false;
bool isDijkstraAnimatingPath = false;
bool dijkstraPathFound = false;

int dijkstraPathIndex = 0;



void startDijkstra() {
    for (auto& cell : grid) {
        cell.visited = false;
        cell.isPath = false;
    }

    pq = decltype(pq)();
    distanceCost.assign(ROWS * COLS,
                        std::numeric_limits<int>::max()); //infinity - no top limit
    dijkstraParent.assign(ROWS * COLS, -1);
    dijkstraPath.clear();

    isDijkstraSearching = true;
    isDijkstraAnimatingPath = false;
    dijkstraPathFound = false;
    dijkstraPathIndex = 0;

    int start = indexOf(startRow, startCol);

    distanceCost[start] = 0;
    pq.push({0, start});
}

// path reconstruction 
void reconstructDijkstraPath() {
    int start = indexOf(startRow, startCol);
    int goal = indexOf(goalRow, goalCol);

    int current = goal;

    while (current != start) {
        dijkstraPath.push_back(current);
        current = dijkstraParent[current];
    }

    dijkstraPath.push_back(start);

    std::reverse(dijkstraPath.begin(),
                 dijkstraPath.end());

    dijkstraPathIndex = 0;
    isDijkstraAnimatingPath = true;
}


void updateDijkstra() {
    if (!isDijkstraSearching) return;

    if (pq.empty()) {
        isDijkstraSearching = false;
        dijkstraPathFound = false;
        std::cout << "No path found!" << std::endl;
        return;
    }

    auto [currentDistance, current] = pq.top();
    pq.pop();

    // Ignore outdated queue entries
    if (currentDistance != distanceCost[current]) {
        return;
    }

    int goal = indexOf(goalRow, goalCol);

    if (current == goal) {
        isDijkstraSearching = false;
        dijkstraPathFound = true;

        reconstructDijkstraPath();

        std::cout << "Dijkstra: Goal reached!"
                  << std::endl;
        return;
    }

    grid[current].visited = true;

    int row = current / COLS;
    int col = current % COLS;

    int directions[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    for (auto& direction : directions) {
        int newRow = row + direction[0];
        int newCol = col + direction[1];

        if (newRow < 0 || newRow >= ROWS ||
            newCol < 0 || newCol >= COLS) {
            continue;
        }

        int neighbour = indexOf(newRow, newCol);

        if (grid[neighbour].isWall) {
            continue;
        }

        // relaxation - if a cheaper way to reach this neighbour, update its distance and remember the new parent
        int newDistance = currentDistance + 1;

        if (newDistance < distanceCost[neighbour]) {
            distanceCost[neighbour] = newDistance;
            dijkstraParent[neighbour] = current;

            pq.push({newDistance, neighbour});
        }
    }
}

// path animation
void updateDijkstraPathAnimation() {
    if (!isDijkstraAnimatingPath) return;

    if (dijkstraPathIndex >=
        static_cast<int>(dijkstraPath.size())) {
        isDijkstraAnimatingPath = false;
        return;
    }

    int index = dijkstraPath[dijkstraPathIndex];

    grid[index].isPath = true;

    dijkstraPathIndex++;
}
