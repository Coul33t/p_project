//
// Created by couland-q on 25/10/22.
//

#include "../include/map.h"

Map::Map() {

}

Map::~Map() {

}

void Map::init(size_t x, size_t y) {
    for (size_t i = 0; i < x * y; i++) {
        this->tiles.emplace_back(Tile());
    }

    this->vertices_array.setPrimitiveType(sf::Quads);
    // *4 because quads
    this->vertices_array.resize(this->size.w * this->size.h * 4);
    std::cout << "Init" << std::endl;
}

void Map::updateTile(const Rectangle& pos, const Rectangle& text_pos) {
    int idx = quadIdx(pos.getRectAsPosVA());

    // If the vertex has been found, just update its texture coordinates
    if(idx != -1) {
        sf::VertexArray text_va = text_pos.getRectAsTextVA();
        this->vertices_array[idx].texCoords = text_va[0].texCoords;
        this->vertices_array[idx + 1].texCoords = text_va[1].texCoords;
        this->vertices_array[idx + 2].texCoords = text_va[2].texCoords;
        this->vertices_array[idx + 3].texCoords = text_va[3].texCoords;
    }

    // Else, add it to the vertices list
    else {
        sf::VertexArray pos_va = pos.getRectAsPosVA();
        sf::VertexArray text_va = text_pos.getRectAsTextVA();

        idx = this->vertices_array.getVertexCount();

        this->vertices_array.append(sf::Vertex(pos_va[0].position, pos_va[0].texCoords));
        this->vertices_array.append(sf::Vertex(pos_va[1].position, pos_va[1].texCoords));
        this->vertices_array.append(sf::Vertex(pos_va[2].position, pos_va[2].texCoords));
        this->vertices_array.append(sf::Vertex(pos_va[3].position, pos_va[3].texCoords));
    }
}

int Map::quadIdx(const sf::VertexArray& quad) {
    for (size_t i = 0; i < this->vertices_array.getVertexCount(); i += 4) {
        if (quad[0].position == this->vertices_array[i].position   &&
            quad[1].position == this->vertices_array[i+1].position &&
            quad[2].position == this->vertices_array[i+2].position &&
            quad[3].position == this->vertices_array[i+3].position) {

            return static_cast<int>(i);
        }
    }

    return -1;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &(this->tileset);
    target.draw(this->vertices_array, states);
}