#include "Map.h"
#include <set>

Map::Map(const std::vector<std::vector<int>>& grid) {
    _grid = grid;
    _rows = grid.size();
    _cols = grid[0].size();

    // scan once at construction so horsePos() is O(1) later
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            if (_grid[r][c] == 2) {
                _horse = {r, c};
            }
        }
    }
}

int Map::rows() const {
    return _rows;
}

int Map::cols() const {
    return _cols;
}

int Map::at(int row, int col) const {
    return _grid[row][col];
}

bool Map::inBounds(int row, int col) const {
    return row >= 0 && row < _rows && col >= 0 && col < _cols;
}

std::pair<int,int> Map::horsePos() const {
    return _horse;
}

void Map::display() const {
    const std::string GREEN  = "\033[32m";
    const std::string BLUE   = "\033[34m";
    const std::string RED    = "\033[31m";
    const std::string RESET  = "\033[0m";

    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            if      (_grid[r][c] == 0) std::cout << GREEN << "0 " << RESET;
            else if (_grid[r][c] == 1) std::cout << BLUE  << "1 " << RESET;
            else if (_grid[r][c] == 2) std::cout << RED   << "2 " << RESET;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Map::displayPaths(const std::vector<std::pair<int,int>>& pathTiles) const {
    const std::string GREEN  = "\033[32m";
    const std::string GREY   = "\033[90m";
    const std::string BLUE   = "\033[34m";
    const std::string RED    = "\033[31m";
    const std::string RESET  = "\033[0m";

    std::set<std::pair<int,int>> pathSet(pathTiles.begin(), pathTiles.end());

    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _cols; c++) {
            if (_grid[r][c] == 1)      std::cout << BLUE  << "1 " << RESET;
            else if (_grid[r][c] == 2) std::cout << RED   << "2 " << RESET;
            else if (pathSet.count({r, c})) std::cout << GREEN << "0 " << RESET;
            else                            std::cout << GREY  << "0 " << RESET;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int Map::countGrass() const {
    int count = 0;
    for (int r = 0; r < _rows; r++)
        for (int c = 0; c < _cols; c++)
            if (_grid[r][c] == 0) count++;
    return count;
}
