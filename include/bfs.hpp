
#pragma once

#include <queue>
#include <vector>

// BFS state
extern std::queue<int> frontier;
extern std::vector<int> parent;
extern std::vector<int> path;

extern bool isSearching;
extern bool isAnimatingPath;
extern bool pathFound;

extern int pathIndex;

// BFS functions
void startBFS();
void updateBFS();
void reconstructPath();
void updatePathAnimation();
