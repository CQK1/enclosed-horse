#include <iostream>
#include "BFS.h"
#include "Map.h"

int main() {

    std::vector<std::vector<int>> data = {
        {1,1,0,1,1,1,0,1,1,1,1,1,1,1,1},
        {1,1,0,1,1,1,0,0,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,0,1,1,1,1,0,1,1,1},
        {0,0,0,1,1,1,0,1,1,1,1,0,1,1,1},
        {0,0,0,1,1,1,0,1,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {1,1,0,1,1,1,0,1,0,0,0,0,0,0,0},
        {1,1,0,1,1,1,0,1,1,0,1,1,1,0,1},
        {0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
        {1,1,0,1,1,1,0,1,1,0,1,1,1,0,1},
        {1,1,0,1,1,1,0,1,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,0,0,0,1,1,0,1,1,0},
        {1,1,0,1,1,1,0,1,0,1,1,0,1,1,0},
        {1,1,0,1,1,1,0,1,0,1,1,0,1,1,0},
        {1,1,0,0,0,0,0,1,0,0,0,0,0,0,0}
    };

    Map m(data);
    std::vector<std::pair<int,int>> tiles = findShortestPathTiles(m);
    int G = m.countGrass();
    int P = (int)tiles.size() - 1;
    double exponentReduction = (1.0 - (double)P / G) * 100.0;

    std::cout << "\nDRIVER 3: Before Optimization\n" << std::endl;
    std::cout << "Tiles (n) that go into the solver = " << G << "\n\n";
    m.display();

    std::cout << "\nDRIVER 3: After Optimization\n" << std::endl;
    std::cout << "Tiles (n) that go into the solver = " << P << "\n\n";
    m.displayPaths(tiles);

    std::cout << "As the solver's time complexity is O(2^n).\n"
	         "Our original amount of operations was 2^" << G <<
	         ".\nNow our amount of operations is 2^" << P <<
	         ".\nThis is a " << exponentReduction <<
	         "% reduction in the solver's search space exponent.\n\n";

    return 0;
}
