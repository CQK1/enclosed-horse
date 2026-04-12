#pragma once
#include "Map.h"
#include <vector>

// Returns a deduplicated vector of all tiles that lie on any
// shortest path from the horse to a border grass tile
std::vector<std::pair<int,int>> findShortestPathTiles(const Map& map);
