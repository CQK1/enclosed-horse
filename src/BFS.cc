#include "BFS.h"
#include <queue>


bool hasInwardGrassNeighbour(const Map& map, int r, int c) {
    int rows = map.rows();
    int cols = map.cols();

    const std::vector<std::pair<int,int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (auto [dr, dc] : directions) {
        int nr = r + dr;
        int nc = c + dc;

        bool isNonBorder = nr > 0 && nr < rows - 1 && nc > 0 && nc < cols - 1;

        if (map.inBounds(nr, nc) && isNonBorder && map.at(nr, nc) == 0) {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int,int>> getBorderTiles(const Map& map,
    const std::vector<std::vector<int>>& dist) {

    int rows = map.rows();
    int cols = map.cols();
    std::vector<std::pair<int,int>> border;

    for (int c = 0; c < cols; c++) {
        if (dist[0][c] != -1 && hasInwardGrassNeighbour(map, 0, c))
            border.push_back({0, c});
        if (dist[rows-1][c] != -1 && hasInwardGrassNeighbour(map, rows-1, c))
            border.push_back({rows-1, c});
    }
    for (int r = 1; r < rows - 1; r++) {
        if (dist[r][0] != -1 && hasInwardGrassNeighbour(map, r, 0))
            border.push_back({r, 0});
        if (dist[r][cols-1] != -1 && hasInwardGrassNeighbour(map, r, cols-1))
            border.push_back({r, cols-1});
    }
    return border;
}

//Traces from one border tile back to the horse using BFS shortest path
void tracePath(const Map& map,
               const std::vector<std::vector<int>>& dist,
               std::pair<int,int> start,
               std::vector<std::vector<bool>>& visited,
               std::vector<std::pair<int,int>>& pathTiles) {

    const std::vector<std::pair<int,int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    std::queue<std::pair<int,int>> q;

    if (visited[start.first][start.second]) return;
    visited[start.first][start.second] = true;
    pathTiles.push_back(start);
    q.push(start);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;

            if (map.inBounds(nr, nc) &&
                !visited[nr][nc] &&
                dist[nr][nc] != -1 &&
                dist[nr][nc] == dist[r][c] - 1) {

                visited[nr][nc] = true;
                pathTiles.push_back({nr, nc});
                q.push({nr, nc});
            }
        }
    }
}

std::vector<std::pair<int,int>> findShortestPathTiles(const Map& map) {

    int rows = map.rows();
    int cols = map.cols();

    const std::vector<std::pair<int,int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    //We perform BFS outward from the horse and keep unreachable tiles as -1
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, -1));
    std::queue<std::pair<int,int>> q;

    auto [hr, hc] = map.horsePos();
    dist[hr][hc] = 0;
    q.push({hr, hc});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;

            if (map.inBounds(nr, nc) &&
                dist[nr][nc] == -1 &&
                map.at(nr, nc) == 0) {

                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    //Using our dist vector with the list of unreachable tiles,
    //we make the list of ideal tiles for BFS again.
    std::vector<std::pair<int,int>> borderTiles = getBorderTiles(map, dist);

    if (borderTiles.empty()) return {};

    //Trace all valid border tiles back to the horse
    //Record the tiles in their shortest path into pathTiles
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::pair<int,int>> pathTiles;

    visited[hr][hc] = true;
    pathTiles.push_back({hr, hc});

    for (auto& borderTile : borderTiles) {
        tracePath(map, dist, borderTile, visited, pathTiles);
    }

    return pathTiles;
}
