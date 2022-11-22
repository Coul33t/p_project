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
    int current_drawing_layer = 0;

    friend std::ostream& operator <<(std::ostream& os, const EditorParams ep) {
        os << "Size: w = " << ep.size.w << " / h = " << ep.size.h << std::endl;
        os << "Scroll speed: " << ep.scroll_speed << std::endl;
        os << "Rectangle to draw: x = " << ep.rect_to_draw.x << " / y = " << ep.rect_to_draw.y << std::endl;
        os << "                   w = " << ep.rect_to_draw.w << " / h = " << ep.rect_to_draw.h << std::endl;
        os << "Current drawing layer: " << ep.current_drawing_layer << std::endl;

        return os;
    }
};

struct TilesetParams {
    Size size;
    sf::Vector2<int> pos;
    int tile_size;
    Rectangle tileset_part_to_draw; // Part of the tileset to draw on the right of the screen
    Rectangle rect_to_draw_on_map; // Rectangle on the tileset to draw on the map
    sf::Vector2<int> selection_size;
    sf::Vector2<int> offset;

    TilesetParams() {
        selection_size = sf::Vector2<int>(1, 1);
    }

    friend std::ostream& operator <<(std::ostream& os, const TilesetParams tp) {
        os << "Position: x = " << tp.pos.x << " / y = " << tp.pos.y << std::endl;
        os << "Size: w = " << tp.size.w << " / h = " << tp.size.h << std::endl;
        os << "Tile size: " << tp.tile_size << std::endl;
        os << "Tileset part to draw: x = " << tp.tileset_part_to_draw.x << " / y = " << tp.tileset_part_to_draw.y << std::endl;
        os << "                      w = " << tp.tileset_part_to_draw.w << " / h = " << tp.tileset_part_to_draw.h << std::endl;

        return os;
    }
};

#endif //P_PROJECT_PARAMS_H
