//
// Created by couland-q on 07/11/22.
//

#ifndef P_PROJECT_SPRITE_H
#define P_PROJECT_SPRITE_H

#include <SFML/Graphics.hpp>

struct Sprite {
    sf::Texture texture;
    sf::Sprite sprite;

    Sprite() = default;

    explicit Sprite(const sf::Texture& text) {
        this->texture = text;
        this->sprite.setTexture(this->texture);
    }

    void setTexture(const sf::Texture& text) {
        this->texture = text;
        this->sprite.setTexture(this->texture);
    }

    sf::Vector2u getSize() const {
        return this->texture.getSize();
    }
};
#endif //P_PROJECT_SPRITE_H
