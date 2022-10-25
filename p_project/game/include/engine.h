//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_ENGINE_H
#define P_PROJECT_ENGINE_H

#include "world.h"

class Engine {
public:
    Engine();
    ~Engine();

    void init();
    void run();

    World world;
};
#endif //P_PROJECT_ENGINE_H
