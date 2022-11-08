//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_PARAMS_H
#define P_PROJECT_PARAMS_H

#include "../../tools/include/tools.h"

struct EditorParams {
    Size size;
    int scroll_speed = 4;
    Rectangle rect_to_draw;

    friend std::ostream& operator <<(std::ostream& os, const EditorParams ep) {
        os << "Size: w = " << ep.size.w << " / h = " << ep.size.h << std::endl;
        os << "Scroll speed: " << ep.scroll_speed << std::endl;
        os << "Rectangle to draw: x = " << ep.rect_to_draw.x << " / y = " << ep.rect_to_draw.y << std::endl;
        os << "                   w = " << ep.rect_to_draw.w << " / h = " << ep.rect_to_draw.h << std::endl;

        return os;
    }
};

struct TilesetParams {
    Size size;
    sf::Vector2<int> pos;
    int tile_size;
    Rectangle rect_to_draw;
    Rectangle rect_to_draw_on_map;
    sf::Vector2<int> offset;

    friend std::ostream& operator <<(std::ostream& os, const TilesetParams tp) {
        os << "Position: x = " << tp.pos.x << " / y = " << tp.pos.y << std::endl;
        os << "Size: w = " << tp.size.w << " / h = " << tp.size.h << std::endl;
        os << "Tile size: " << tp.tile_size << std::endl;
        os << "Rectangle to draw: x = " << tp.rect_to_draw.x << " / y = " << tp.rect_to_draw.y << std::endl;
        os << "                   w = " << tp.rect_to_draw.w << " / h = " << tp.rect_to_draw.h << std::endl;

        return os;
    }
};

#endif //P_PROJECT_PARAMS_H
