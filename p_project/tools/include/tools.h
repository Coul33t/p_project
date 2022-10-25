//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_TOOLS_H
#define P_PROJECT_TOOLS_H

#include <cstddef>

#include <raylib.h>

struct Size {
    int w, h;

    Size() {
        w = 0;
        h = 0;
    }

    Size(int h, int w): h(h), w(w) {}
};

struct Position {
    int x, y;

    Position() {
        x = 0;
        y = 0;
    }

    Position (int x, int y): x(x), y(y) {}
};

namespace Tools {
    bool isInRectangle(Vector2 mouse_pos, int x, int y, int w, int h);
}


#endif //P_PROJECT_TOOLS_H
