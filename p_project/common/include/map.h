//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_MAP_H
#define P_PROJECT_MAP_H

#include <vector>
#include <iostream>

#include <SFML/System.hpp>

#include "../../../extlib/cereal-1.3.2/include/cereal/archives/xml.hpp"

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

    // Can't separate template definition and declaration
    template <class Archive>
    void serialize(Archive & archive) {
        for (size_t i = 0; i < this->vertices_array.getVertexCount(); i++) {
            std::string name = "vertex_" + std::to_string(i);
            archive(cereal::make_nvp(name, VertexStruct(this->vertices_array[i].position.x,
                                                        this->vertices_array[i].position.y,
                                                        this->vertices_array[i].texCoords.x,
                                                        this->vertices_array[i].texCoords.y,
                                                        this->vertices_array[i].color.toInteger())));

            /*std::cout << "Position : (" << this->vertices_array[i].position.x << ", " << this->vertices_array[i].position.y << ")" << std::endl;
            std::cout << "Colour   : " << this->vertices_array[i].color.toInteger() << std::endl;
            std::cout << "TextCoord: (" << this->vertices_array[i].texCoords.x << ", " << this->vertices_array[i].texCoords.y << ")" << std::endl;*/
        }

        archive(CEREAL_NVP(size));
    }

    std::vector<Tile> tiles;
    sf::VertexArray vertices_array;
    sf::Texture tileset;
    Size size;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif //P_PROJECT_MAP_H
