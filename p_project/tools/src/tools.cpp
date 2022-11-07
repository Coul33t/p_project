//
// Created by couland-q on 25/10/22.
//

#include "../include/tools.h"

namespace Tools {
    bool isInRectangle(sf::Vector2<int> mouse_pos, int x, int y, int w, int h) {
        return (mouse_pos.x > x && mouse_pos.x < w + x &&
                mouse_pos.y > y && mouse_pos.y < h + y);
    }

    sf::Vector2<int> getTopLeft(sf::Vector2<int> original_coord, int tile_size) {
        sf::Vector2<int> new_coord;
        new_coord.x = tile_size * (original_coord.x / tile_size);
        new_coord.y = tile_size * (original_coord.y / tile_size);
        return new_coord;
    }

    size_t TransformCoord(int x, int y, size_t col) {
        return ((y * col) + x);
    }

    size_t TransformCoord(sf::Vector2<int> coord, size_t col) {
        return ((coord.y * col) + coord.x);
    }
}
