#include <iostream>
#include "Dijkstra.h"
#include "Map.h"

int main() {

    std::vector<std::vector<int>> data = {
        {0,0,1,1,1,1,0,0,0,1,1,1,1,0,0},
        {1,0,0,0,1,1,1,0,1,1,1,0,0,0,1},
        {0,1,1,0,0,0,0,0,0,0,0,0,1,1,0},
        {0,0,0,1,1,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
        {1,0,0,1,1,0,1,0,1,0,1,1,0,0,1},
        {1,0,0,1,1,1,0,0,0,1,1,1,0,0,1},
        {0,1,0,1,1,0,0,1,0,0,1,1,0,1,0},
        {0,0,0,0,0,0,1,0,2,0,0,0,0,0,0},
        {1,1,0,0,0,0,1,0,0,0,0,0,0,1,1},
        {0,0,1,1,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,0,0,0,1,1,1,0,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {0,1,0,0,0,1,0,1,0,0,0,0,0,1,0},
        {0,0,1,1,1,0,1,0,1,1,0,0,1,0,0}
    };

    Map m(data);
    std::cout << "\nDRIVER 1:\n" << std::endl;
    m.display();

    std::vector<std::pair<int, int>> candidates = Dijkstra::findCandiateWalls(m);

    std::cout << "After the operation, there are " << candidates.size() << " candidate walls" << std::endl;
    std::cout << "\nCells that are on any of the shortest paths:" << std::endl;
    
    for (auto p : candidates) {
        std::cout << "(" << p.first << ", " << p.second << ") ";
    }
    std::cout << "\n" << std::endl;

    return 0;
}