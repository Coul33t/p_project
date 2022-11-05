//
// Created by couland-q on 25/10/22.
//

#include "../include/editor.h"

Editor::Editor() = default;

Editor::~Editor() = default;

void Editor::init(int w, int h, int tile_size) {
    this->params.size.w = w;
    this->params.size.h = h;
    this->tileset_params.tile_size = tile_size;

    window.create(sf::VideoMode(this->params.size.w, this->params.size.h), "Map Editor");
}

void Editor::open() const {

}

bool Editor::loadTileset(const std::string& path) {
    if(this->tileset.loadFromFile(path)) {
        std::cerr << "[editor.cpp] ERROR: couldn't load texture at " << path << "." << std::endl;
        return false;
    }

    this->tileset_params.size.w = this->tileset.getSize().x;
    this->tileset_params.size.h = this->tileset.getSize().y;

    this->tileset_params.rect_to_draw.x = 0;
    this->tileset_params.rect_to_draw.y = 0;
    this->tileset_params.rect_to_draw.w = this->tileset.getSize().x;
    this->tileset_params.rect_to_draw.h = this->params.size.h;

    return true;
}

void Editor::run() {
    //TODO: see RenderTexture for caching
    tileset_params.pos.x = this->params.size.w - this->tileset.getSize().x;
    tileset_params.pos.y = 0;

    while (this->window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (this->window.pollEvent(event)) {
            handleEvent(event);

        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }
}

void Editor::handleEvent(sf::Event e) {
    switch(e.type) {
        case sf::Event::Closed:
            this->window.close();
            break;

        case sf::Event::MouseButtonPressed:
            this->handleMouseInput(e);
            break;

        case sf::Event::KeyPressed:
            //this->handleInput();
            break;

        default:
            break;
    }
}

void Editor::handleMouseInput(sf::Event e) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(this->window);
    float new_offset = 0.0;

    // Tileset
    if (Tools::isInRectangle(mouse_pos,
                             params.size.w - tileset_params.size.w, 0,
                             tileset_params.size.w, tileset_params.size.h)) {

        // Tileset scrolling
        if (e.type == sf::Event::MouseWheelMoved) {
            new_offset = e.mouseWheel.delta * params.scroll_speed;

            // If the y value is too high, set it to the max value (end of the tileset - height of the tileset)
            if (tileset_params.rect_to_draw.y - (new_offset * tileset_params.tile_size)
                > tileset_params.size.h - params.size.h) {
                tileset_params.rect_to_draw.y = tileset_params.size.h - params.size.h;
            }

                // If too low, set it to 0 (beginning of the tileset)
            else if (tileset_params.rect_to_draw.y - (new_offset * tileset_params.tile_size) < 0) {
                tileset_params.rect_to_draw.y = 0;
            }

                // Regular scolling
            else {
                // Minus, because a bottom scrolling (negative offset) == y value increasing
                tileset_params.rect_to_draw.y -= new_offset * tileset_params.tile_size;
            }
        }

        // Tile selection
        if(e.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i tileset_pos;
            tileset_pos.x = mouse_pos.x - (params.size.w - tileset_params.size.w);
            tileset_pos.y = tileset_params.rect_to_draw.y + mouse_pos.y;

            // Convert to tile (divide by tilesize and truncate)
            sf::Vector2i new_pos = Tools::getTopLeft(tileset_pos, tileset_params.tile_size);

            params.rect_to_draw.x = new_pos.x;
            params.rect_to_draw.y = new_pos.y;
            params.rect_to_draw.w = tileset_params.tile_size;
            params.rect_to_draw.h = tileset_params.tile_size;
        }
    }

    else if (Tools::isInRectangle(mouse_pos,
                                  0, 0,
                                  params.size.w - tileset_params.size.w, params.size.h)) {

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i new_pos = Tools::getTopLeft(mouse_pos, this->tileset_params.tile_size);
            Rectangle dest;
            dest.x = new_pos.x;
            dest.y = new_pos.y;
            dest.w = new_pos.x + tileset_params.tile_size;
            dest.h = new_pos.y + tileset_params.tile_size;
        }

    }
}