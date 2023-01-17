//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_TOOLS_H
#define P_PROJECT_TOOLS_H

#include <cstddef>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../../../extlib/cereal-1.3.2/include/cereal/archives/xml.hpp"

#define FULL_LOCATION "[" << __FILE__ << " | " << __FUNCTION__ << " | l." << __LINE__ << "]" << std::endl

struct Size {
    int w, h;

    Size() {
        w = 0;
        h = 0;
    }

    Size(int h, int w): h(h), w(w) {}

    template <class Archive>
    void serialize(Archive & archive) {
        archive & w;
        archive & h;
    }
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

    Rectangle(const Rectangle& other_rect) {
        x = other_rect.x;
        y = other_rect.y;
        w = other_rect.w;
        h = other_rect.h;
        x2 = other_rect.x2;
        y2 = other_rect.y2;
        rect.left = other_rect.rect.left;
        rect.top = other_rect.rect.top;
        rect.width = other_rect.rect.width;
        rect.height = other_rect.rect.height;
    }

    sf::Rect<int>& getSFMLRect() {
        return this->rect;
    }

    sf::VertexArray getRectAsPosVA() const {
        sf::VertexArray va(sf::Quads, 4);
        va[0].position = sf::Vector2f(x, y);
        va[1].position = sf::Vector2f(x + w, y);
        va[2].position = sf::Vector2f(x + w, y + h);
        va[3].position = sf::Vector2f(x, y + h);

        return va;
    }

    sf::VertexArray getRectAsTextVA() const {
        sf::VertexArray va(sf::Quads, 4);
        va[0].texCoords = sf::Vector2f(x, y);
        va[1].texCoords = sf::Vector2f(x + w, y);
        va[2].texCoords = sf::Vector2f(x + w, y + h);
        va[3].texCoords = sf::Vector2f(x, y + h);

        return va;
    }
};

struct VertexStruct {
    float pos_x, pos_y, texCoords_x, texCoords_y;
    uint32_t colour;

    VertexStruct(float pos_x, float pos_y, float texCoords_x, float texCoords_y, uint32_t colour):
        pos_x(pos_x), pos_y(pos_y), texCoords_x(texCoords_x), texCoords_y(texCoords_y), colour(colour) {}

    template <class Archive>
    void serialize(Archive& ar) {
        ar(CEREAL_NVP(pos_x),
           CEREAL_NVP(pos_y),
           CEREAL_NVP(texCoords_x),
           CEREAL_NVP(texCoords_y),
           CEREAL_NVP(colour));
    }
};
namespace Tools {
    bool isInRectangle(sf::Vector2<int> mouse_pos, int x, int y, int w, int h);
    sf::Vector2<int> getTopLeft(sf::Vector2<int> original_coord, int tile_size);
    size_t TransformCoord(int x, int y, size_t col);
    size_t TransformCoord(sf::Vector2<int> coord, size_t col);
    sf::VertexArray getRectAsPosVA(const Rectangle& rect);
    sf::VertexArray getRectAsTextVA(const Rectangle& rect);

    template <class T>
    bool isIn(T to_find, std::vector<T> vec) {
        return (std::find(vec.begin(), vec.end(), to_find) != std::end(vec));
    }
}


#endif //P_PROJECT_TOOLS_H
