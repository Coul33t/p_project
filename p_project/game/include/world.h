//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_WORLD_H
#define P_PROJECT_WORLD_H

#include <vector>

#include "map.h"

class World {
public:
    World();
    ~World();

    std::vector<Map> maps;
};
#endif //P_PROJECT_WORLD_H
