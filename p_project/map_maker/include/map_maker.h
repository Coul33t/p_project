//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_MAP_MAKER_H
#define P_PROJECT_MAP_MAKER_H

#include "editor.h"

class MapMaker {
public:
    MapMaker();
    ~MapMaker();

    void init();
    void open();
    void run();

   Editor editor;
};
#endif //P_PROJECT_MAP_MAKER_H
