//
// Created by couland-q on 25/10/22.
//

#include "../include/map.h"

Map::Map() {

}

Map::Map(sf::Texture& tileset_text) {
    this->tileset = tileset_text;
}

Map::~Map() {

}

void Map::init(size_t x, size_t y, sf::Texture& tileset_text) {
    for (size_t i = 0; i < x * y; i++)
        this->tiles.emplace_back(Tile());


    this->vertices_array.setPrimitiveType(sf::Quads);
    // *4 because quads
    this->vertices_array.resize(this->size.w * this->size.h * 4);

    this->tileset = tileset_text;
}

void Map::updateTiles(const Rectangle& pos, const Rectangle& text_pos, size_t tilesize) {

    for (size_t i = 0; i < pos.w; i += tilesize) {
        for (size_t j = 0; j < pos.h; j += tilesize) {
            Rectangle pos_subrect(pos.x + i, pos.y + j,tilesize, tilesize);
            Rectangle text_rect(text_pos.x + i, text_pos.y + j, tilesize, tilesize);

            int idx = quadIdx(Tools::getRectAsPosVA(pos_subrect));

            // If the vertex has been found, only update its texture coordinates
            if(idx != -1) {
                sf::VertexArray text_va = text_rect.getRectAsTextVA();
                this->vertices_array[idx].texCoords = text_va[0].texCoords;
                this->vertices_array[idx + 1].texCoords = text_va[1].texCoords;
                this->vertices_array[idx + 2].texCoords = text_va[2].texCoords;
                this->vertices_array[idx + 3].texCoords = text_va[3].texCoords;
            }

                // Else, add it to the vertices list
            else {
                sf::VertexArray pos_va = pos_subrect.getRectAsPosVA();
                sf::VertexArray text_va = text_rect.getRectAsTextVA();

                this->vertices_array.append(sf::Vertex(pos_va[0].position, text_va[0].texCoords));
                this->vertices_array.append(sf::Vertex(pos_va[1].position, text_va[1].texCoords));
                this->vertices_array.append(sf::Vertex(pos_va[2].position, text_va[2].texCoords));
                this->vertices_array.append(sf::Vertex(pos_va[3].position, text_va[3].texCoords));
            }
        }
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