//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_TILE_H
#define P_PROJECT_TILE_H

#include <SFML/Graphics.hpp>

struct Tile {
    sf::VertexArray quad;

    /**
     * Default constructor for a Tile
     */
    Tile() {
        quad = sf::VertexArray(sf::Quads, 4);
        quad[0].position = sf::Vector2f(-1, -1);
        quad[1].position = sf::Vector2f(-1, -1);
        quad[2].position = sf::Vector2f(-1, -1);
        quad[3].position = sf::Vector2f(-1, -1);
    }

    /**
     * Constructor for a Tile with a position for the quad
     * @param x left coordinate of the quad
     * @param y top coordinate of the quad
     * @param tilesize size of a tile
     */
    Tile(int x, int y, size_t tilesize) {
        quad = sf::VertexArray(sf::Quads, 4);

        quad[0].position = sf::Vector2f(x, y);
        quad[1].position = sf::Vector2f(x + tilesize, y);
        quad[2].position = sf::Vector2f(x + tilesize, y + tilesize);
        quad[3].position = sf::Vector2f(x, y + tilesize);
    }

    /**
     * Constructor for a tile with coordinates for the quad and for the texture
     * @param x left coordinate of the quad
     * @param y top coordinate of the quad
     * @param x_t left coordinate of the texture
     * @param y_t top coordinate of the texture
     * @param tilesize size of a tile
     */
    Tile(int x, int y, int x_t, int y_t, size_t tilesize) {
        quad = sf::VertexArray(sf::Quads, 4);

        quad[0].position = sf::Vector2f(x, y);
        quad[1].position = sf::Vector2f(x + tilesize, y);
        quad[2].position = sf::Vector2f(x + tilesize, y + tilesize);
        quad[3].position = sf::Vector2f(x, y + tilesize);

        quad[0].texCoords = sf::Vector2f(x_t, y_t);
        quad[1].texCoords = sf::Vector2f(x_t + tilesize, y_t);
        quad[2].texCoords = sf::Vector2f(x_t + tilesize, y_t + tilesize);
        quad[3].texCoords = sf::Vector2f(x_t, y_t + tilesize);
    }

    /**
     * Sets the texture position for the vertices
     * @param x_t left coordinate of the texture
     * @param y_t top coordinate of the texture
     * @param tilesize size of a tile
     */
    void setTexturePos(int x_t, int y_t, size_t tilesize) {
        quad[0].texCoords = sf::Vector2f(x_t, y_t);
        quad[1].texCoords = sf::Vector2f(x_t + tilesize, y_t);
        quad[2].texCoords = sf::Vector2f(x_t + tilesize, y_t + tilesize);
        quad[3].texCoords = sf::Vector2f(x_t, y_t + tilesize);
    }
};

#endif //P_PROJECT_TILE_H
