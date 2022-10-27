//
// Created by couland-q on 25/10/22.
//

#include "../include/tools.h"

namespace Tools {
    bool isInRectangle(sf::Vector2i mouse_pos, int x, int y, int w, int h) {
        return (mouse_pos.x > x && mouse_pos.x < w + x &&
                mouse_pos.y > y && mouse_pos.y < h + y);
    }

    sf::Vector2i getTopLeft(sf::Vector2i original_coord, int tile_size) {
        sf::Vector2i new_coord;
        new_coord.x = tile_size * (original_coord.x / tile_size);
        new_coord.y = tile_size * (original_coord.y / tile_size);
        return new_coord;
    }
}
