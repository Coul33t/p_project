//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_TOOLS_H
#define P_PROJECT_TOOLS_H

#include <cstddef>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

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

struct Rectangle {
    int x, y, w, h, x2, y2;
    sf::Rect<int> rect;

    Rectangle() = default;

    Rectangle(int x, int y, int w, int h): x(x), y(y), w(w), h(h) {
        x2 = x + w;
        y2 = y + h;
        rect.left = x;
        rect.top = y;
        rect.width = w;
        rect.height = h;
    }

    sf::Rect<int>& getSFMLRect() {
        return this->rect;
    }
};

namespace Tools {
    bool isInRectangle(sf::Vector2i mouse_pos, int x, int y, int w, int h);
    sf::Vector2i getTopLeft(sf::Vector2i original_coord, int tile_size);
}


#endif //P_PROJECT_TOOLS_H
