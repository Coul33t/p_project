//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_MAP_H
#define P_PROJECT_MAP_H

#include <vector>
#include <iostream>

#include <SFML/System.hpp>

#include "tile.h"
#include "tools.h"

class Map : public sf::Drawable, public sf::Transformable {
public:
    Map();
    Map(sf::Texture& tileset_text);
    ~Map();

    void init(size_t x, size_t y, sf::Texture& tileset_text);

    void updateTiles(const Rectangle& pos, const Rectangle& text_pos, size_t tilesize);

    int quadIdx(const sf::VertexArray& quad);

    void serialise();

    std::vector<Tile> tiles;
    sf::VertexArray vertices_array;
    sf::Texture tileset;
    Size size;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif //P_PROJECT_MAP_H
