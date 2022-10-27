//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_MAP_H
#define P_PROJECT_MAP_H

#include <vector>

#include "tile.h"
#include "tools.h"

class Map {
public:
    Map();
    ~Map();

    std::vector<Tile> tiles;
    Size size;

};
#endif //P_PROJECT_MAP_H
