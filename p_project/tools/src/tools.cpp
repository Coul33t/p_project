//
// Created by couland-q on 25/10/22.
//

#include "../include/tools.h"

namespace Tools {
    bool isInRectangle(Vector2 mouse_pos, int x, int y, int w, int h) {
        return (mouse_pos.x > x && mouse_pos.x < w + x &&
                mouse_pos.y > y && mouse_pos.y < h + y);
    }
}
