//
// Created by couland-q on 25/10/22.
//

#include "../include/editor.h"

Editor::Editor() = default;

Editor::~Editor() = default;

void Editor::init(int w, int h, int tile_size) {
    params.size.w = w;
    params.size.h = h;
    tileset_params.tile_size = tile_size;

    window.create(sf::VideoMode(params.size.w, params.size.h), "Map Editor");
}

void Editor::initMap(int w, int h) {
    this->map.init(w, h, this->tileset.texture);
}

void Editor::open() const {

}

bool Editor::loadTileset(const std::string& path) {
    sf::Texture tileset_text;
    if(!tileset_text.loadFromFile(path)) {
        std::cerr << FULL_LOCATION
                  << "ERROR: couldn't load texture at " << path << "." << std::endl;
        return false;
    }

    this->map.tileset = tileset_text;

    this->tileset.setTexture(tileset_text);

    tileset_params.size.w = this->tileset.getSize().x;
    tileset_params.size.h = this->tileset.getSize().y;

    // Set the upper-left tile as the first one selected
    tileset_params.rect_to_draw_on_map.x = params.size.w - tileset_params.size.w;
    tileset_params.rect_to_draw_on_map.y = 0;
    tileset_params.rect_to_draw_on_map.w = tileset_params.tile_size;
    tileset_params.rect_to_draw_on_map.h = tileset_params.tile_size;

    tileset_params.rect_to_draw.x = 0;
    tileset_params.rect_to_draw.y = 0;
    tileset_params.rect_to_draw.w = tileset_params.size.w;
    tileset_params.rect_to_draw.h = params.size.h;

    tileset_params.offset.x = params.size.w - tileset_params.size.w;
    tileset_params.offset.y = 0;

    return true;
}

void Editor::drawOverlayingShapes() {
    // Draw the current selected tile
    sf::RectangleShape rectangle(sf::Vector2f(tileset_params.tile_size, tileset_params.tile_size));
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setPosition(tileset_params.rect_to_draw_on_map.x + tileset_params.offset.x,
                          tileset_params.rect_to_draw_on_map.y - tileset_params.rect_to_draw.y + tileset_params.offset.y);
    this->window.draw(rectangle);
}

void Editor::run() {
    //TODO: see RenderTexture for caching
    tileset_params.pos.x = params.size.w - this->tileset.getSize().x;
    tileset_params.pos.y = 0;
    this->tileset.sprite.setPosition(tileset_params.pos.x, tileset_params.pos.y);

    while (this->window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (this->window.pollEvent(event)) {
            handleEvent(event);

        }

        // clear the window with black color
        window.clear(sf::Color(240, 226, 182));

        window.draw(this->tileset.sprite);
        drawOverlayingShapes();
        window.draw(this->map);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }
}

void Editor::handleEvent(sf::Event e) {
    status.update();

    switch(e.type) {
        case sf::Event::Closed:
            this->window.close();
            break;

        case sf::Event::MouseButtonPressed:
            status.current_status = Status::DRAGGING;
            this->handleMouseInput(e);
            break;

        case sf::Event::MouseButtonReleased:
            status.current_status = Status::NONE;
            //std::cout << "Status None" << std::endl;
            this->handleMouseInput(e);
            break;

        case sf::Event::MouseMoved:
            if (status.current_status == Status::DRAGGING) {
                this->handleMouseInput(e);
            }
            break;

        case sf::Event::MouseWheelMoved:
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
    this->mouse_coord.old_coord = this->mouse_coord.new_coord;
    this->mouse_coord.new_coord = sf::Mouse::getPosition(this->window);
    float new_offset = 0.0;

    // Tileset
    // TODO: take care of dragging inside to have a big rectangle selection
    if (Tools::isInRectangle(this->mouse_coord.new_coord,
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

            this->tileset.sprite.setTextureRect(sf::IntRect(tileset_params.rect_to_draw.x,
                                                            tileset_params.rect_to_draw.y,
                                                            tileset_params.rect_to_draw.w,
                                                            tileset_params.rect_to_draw.h));
        }

        // Tile selection
        if(e.type == sf::Event::MouseButtonPressed) {
            // If you're dragging on the tileset, you want a bigger rectangle selection
            if (this->status.sameAsLast() && this->status.current_status == Status::DRAGGING && mouseIsInNewTile(this->mouse_coord.old_coord, this->mouse_coord.new_coord)) {
                sf::Vector2<int> old_top_left = Tools::getTopLeft(this->mouse_coord.old_coord, tileset_params.tile_size);
                sf::Vector2<int> new_top_left = Tools::getTopLeft(this->mouse_coord.new_coord, tileset_params.tile_size);

                //TODO: do lol
            }

            // Selected a single tile
            else {
                sf::Vector2i tileset_pos;
                tileset_pos.x = this->mouse_coord.new_coord.x - (params.size.w - tileset_params.size.w);
                tileset_pos.y = this->mouse_coord.new_coord.y;

                // Convert to tile (divide by tilesize and truncate)
                sf::Vector2i new_pos = Tools::getTopLeft(tileset_pos, tileset_params.tile_size);

                tileset_params.rect_to_draw_on_map.x = new_pos.x;
                tileset_params.rect_to_draw_on_map.y = new_pos.y + this->tileset_params.rect_to_draw.y;
                tileset_params.rect_to_draw_on_map.w = tileset_params.tile_size;
                tileset_params.rect_to_draw_on_map.h = tileset_params.tile_size;
            }

        }
    }

    // Map
    else if (Tools::isInRectangle(this->mouse_coord.new_coord,
                                  0, 0,
                                  params.size.w - tileset_params.size.w, params.size.h)) {

        // Regular click
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Avoid endlessly resetting the same map tile to the same tileset tile
            if (this->status.current_status == Status::DRAGGING && !mouseIsInNewTile(this->mouse_coord.old_coord, this->mouse_coord.new_coord)) {
                return;
            }

            sf::Vector2<int> new_pos = Tools::getTopLeft(this->mouse_coord.new_coord, tileset_params.tile_size);
            Rectangle dest;
            dest.x = new_pos.x;
            dest.y = new_pos.y;
            dest.w = tileset_params.tile_size;
            dest.h = tileset_params.tile_size;

            this->map.updateTile(dest, tileset_params.rect_to_draw_on_map);
        }

    }
}

bool Editor::mouseIsInNewTile(sf::Vector2<int> old_coord, sf::Vector2<int> new_coord) {
    sf::Vector2<int> old_top_left = Tools::getTopLeft(old_coord, tileset_params.tile_size);
    sf::Vector2<int> new_top_left = Tools::getTopLeft(new_coord, tileset_params.tile_size);

    return (old_top_left.x != new_top_left.x || old_top_left.y != new_top_left.y);
}