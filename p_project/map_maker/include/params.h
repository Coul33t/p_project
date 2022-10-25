//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_PARAMS_H
#define P_PROJECT_PARAMS_H

#include "../../tools/include/tools.h"

struct EditorParams {
    Size size;
    int scroll_speed = 16;

};

struct TilesetParams {
    Size size;
    Vector2 pos;
    int tile_size;
    Rectangle rect_to_draw;


    friend std::ostream& operator <<(std::ostream& os, const TilesetParams tp) {
        os << "Position: x = " << tp.pos.x << " / y = " << tp.pos.y << std::endl;
        os << "Size: w = " << tp.size.w << " / h = " << tp.size.h << std::endl;
        os << "Tile size: " << tp.tile_size << std::endl;
        os << "Rectangle to draw: x = " << tp.rect_to_draw.x << " / y = " << tp.rect_to_draw.y << std::endl;
        os << "                   w = " << tp.rect_to_draw.width << " / h = " << tp.rect_to_draw.height << std::endl;

        return os;
    }
};

#endif //P_PROJECT_PARAMS_H
