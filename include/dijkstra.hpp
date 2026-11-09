
#pragma once

#include <queue>
#include <vector>

extern std::priority_queue<std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>> pq; //priority queue; processes the lowest-cost cell first

extern std::vector<int> distanceCost; //stores the cheapest known distance to each cell
extern std::vector<int> dijkstraParent; //remember the previous cell for path reconstruction
extern std::vector<int> dijkstraPath; // final shortest path

extern bool isDijkstraSearching;
extern bool isDijkstraAnimatingPath;
extern bool dijkstraPathFound;

extern int dijkstraPathIndex; //current position in the path animation

void startDijkstra();
void updateDijkstra();
void reconstructDijkstraPath();
void updateDijkstraPathAnimation();
