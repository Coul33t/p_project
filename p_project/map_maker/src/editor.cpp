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
    map.init(w, h, tileset.texture);
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

    map.tileset = tileset_text;

    tileset.setTexture(tileset_text);

    tileset_params.size.w = tileset.getSize().x;
    tileset_params.size.h = tileset.getSize().y;

    // Set the upper-left tile as the first one selected
    tileset_params.rect_to_draw_on_map.x = params.size.w - tileset_params.size.w;
    tileset_params.rect_to_draw_on_map.y = 0;
    tileset_params.rect_to_draw_on_map.w = tileset_params.tile_size;
    tileset_params.rect_to_draw_on_map.h = tileset_params.tile_size;

    tileset_params.tileset_part_to_draw.x = 0;
    tileset_params.tileset_part_to_draw.y = 0;
    tileset_params.tileset_part_to_draw.w = tileset_params.size.w;
    tileset_params.tileset_part_to_draw.h = params.size.h;

    tileset_params.offset.x = params.size.w - tileset_params.size.w;
    tileset_params.offset.y = 0;

    return true;
}

void Editor::drawInterface() {

}

void Editor::drawOverlayingShapes() {
    // Draw the current selected tile
    sf::RectangleShape rectangle(sf::Vector2f(tileset_params.tile_size * this->tileset_params.selection_size.x,
                                              tileset_params.tile_size * this->tileset_params.selection_size.y));

    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setPosition(tileset_params.rect_to_draw_on_map.x + tileset_params.offset.x,
                          tileset_params.rect_to_draw_on_map.y - tileset_params.tileset_part_to_draw.y + tileset_params.offset.y);
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

        // clear the window with cream color
        window.clear(sf::Color(240, 226, 182));


        window.draw(this->map);

        window.draw(this->tileset.getRectShape(tileset_params.pos.x, tileset_params.pos.y, sf::Color(240, 226, 182)));
        window.draw(this->tileset.sprite);
        drawOverlayingShapes();

        // end the current frame
        window.display();
    }
}

void Editor::handleEvent(sf::Event e) {
    status.update();

    if (e.type == sf::Event::Closed) {
        this->window.close();
    }

    else if(Tools::isIn(e.type, MOUSE_EVENTS)) {
        bool handle = false;

        if (e.type == sf::Event::MouseButtonPressed) {
            status.current_status = Status::DRAGGING;
            handle = true;
        }

        else if (e.type == sf::Event::MouseButtonReleased) {
            status.current_status = Status::NONE;
            handle = true;
        }

        else if (e.type == sf::Event::MouseWheelMoved) {
            handle = true;
        }

        else if (e.type == sf::Event::MouseMoved) {
            if (status.current_status == Status::DRAGGING) {
                handle = true;
            }
        }

        if (handle) {
            this->handleMouseInput(e);
        }
    }

    else if(Tools::isIn(e.type, KEY_EVENTS)) {

    }
}

void Editor::handleMouseInput(sf::Event& e) {
    this->mouse_coord.old_coord = this->mouse_coord.new_coord;
    this->mouse_coord.new_coord = sf::Mouse::getPosition(this->window);

    // Tileset
    // TODO: take care of dragging inside to have a big rectangle selection
    if (Tools::isInRectangle(this->mouse_coord.new_coord,
                             params.size.w - tileset_params.size.w, 0,
                             tileset_params.size.w, tileset_params.size.h)) {

        // Tileset scrolling
        if (e.type == sf::Event::MouseWheelMoved) {
            handleTilesetScrolling(e);
        }

        // Single tile selection
        if(e.type == sf::Event::MouseButtonPressed) {
            handleTileSelection();
        }

        // Dragging on the selection
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // TODO: use to get back into already dragged selection rectangle
            origin_of_drag = mouse_coord;
            // If you're dragging on the tileset, you want a bigger rectangle selection
            if (this->status.sameAsLast()
                && this->status.current_status == Status::DRAGGING
                && mouseIsInNewTile(this->mouse_coord.old_coord, this->mouse_coord.new_coord)) {
                handleTilesetDragging();
            }
        }
    }

    // Map
    else if (Tools::isInRectangle(this->mouse_coord.new_coord, 0, 0,
                                  params.size.w - tileset_params.size.w, params.size.h)) {

        // Regular click or dragging
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            handleMapLeftClick();
        }
    }
}

void Editor::handleTilesetScrolling(sf::Event& e) {
    float new_offset = e.mouseWheel.delta * params.scroll_speed;


    // If the y value is too high, set it to the max value (end of the tileset - height of the tileset)
    if (tileset_params.tileset_part_to_draw.y - (new_offset * tileset_params.tile_size)
        > tileset_params.size.h - params.size.h) {
        tileset_params.tileset_part_to_draw.y = tileset_params.size.h - params.size.h;
    }

        // If too low, set it to 0 (beginning of the tileset)
    else if (tileset_params.tileset_part_to_draw.y - (new_offset * tileset_params.tile_size) < 0) {
        tileset_params.tileset_part_to_draw.y = 0;
    }

        // Regular scolling
    else {
        // Minus, because a bottom scrolling (negative offset) == y value increasing
        tileset_params.tileset_part_to_draw.y -= new_offset * tileset_params.tile_size;
    }

    this->tileset.sprite.setTextureRect(sf::IntRect(tileset_params.tileset_part_to_draw.x,
                                                    tileset_params.tileset_part_to_draw.y,
                                                    tileset_params.tileset_part_to_draw.w,
                                                    tileset_params.tileset_part_to_draw.h));
}

void Editor::handleTileSelection() {
    sf::Vector2i tileset_pos;
    tileset_pos.x = this->mouse_coord.new_coord.x - (params.size.w - tileset_params.size.w);
    tileset_pos.y = this->mouse_coord.new_coord.y;

    // Convert to tile (divide by tilesize and truncate)
    sf::Vector2i new_pos = Tools::getTopLeft(tileset_pos, tileset_params.tile_size);

    tileset_params.rect_to_draw_on_map.x = new_pos.x;
    tileset_params.rect_to_draw_on_map.y = new_pos.y + this->tileset_params.tileset_part_to_draw.y;
    tileset_params.rect_to_draw_on_map.w = tileset_params.tile_size;
    tileset_params.rect_to_draw_on_map.h = tileset_params.tile_size;

    tileset_params.selection_size.x = 1;
    tileset_params.selection_size.y = 1;
}

void Editor::handleTilesetDragging() {
    sf::Vector2<int> old_top_left = Tools::getTopLeft(this->mouse_coord.old_coord, tileset_params.tile_size);
    sf::Vector2<int> new_top_left = Tools::getTopLeft(this->mouse_coord.new_coord, tileset_params.tile_size);

    //TODO: check if mouse is going back into selection

    // If new_x > old_x and new_y > old_y : change size of selection +1/+1 (easy case)
    if (new_top_left.x > old_top_left.x && new_top_left.y > old_top_left.y) {
        this->tileset_params.selection_size.x += 1;
        this->tileset_params.selection_size.y += 1;
    }

    // If new_x > old_x and new_y == old_y : change size of selection +1/0 (easy case)
    else if (new_top_left.x > old_top_left.x && new_top_left.y == old_top_left.y) {
        this->tileset_params.selection_size.x += 1;
    }

    // If new_x == old_x and new_y > old_y : change size of selection 0/+1 (easy case)
    else if (new_top_left.x == old_top_left.x && new_top_left.y > old_top_left.y) {
        this->tileset_params.selection_size.y += 1;
    }

    // If new_x < old_x and new_y < old_y : change size of selection +1/+1 AND Change origin -1/-1
    else if (new_top_left.x < old_top_left.x && new_top_left.y < old_top_left.y) {
        this->tileset_params.selection_size.x += 1;
        this->tileset_params.selection_size.y += 1;
        this->tileset_params.rect_to_draw_on_map.x -= tileset_params.tile_size;
        this->tileset_params.rect_to_draw_on_map.y -= tileset_params.tile_size;
    }

    // If new_x < old_x and new_y == old_y :  change size of selection +1/0 AND Change origin -1/0
    else if (new_top_left.x < old_top_left.x && new_top_left.y == old_top_left.y) {
        this->tileset_params.selection_size.x += 1;
        this->tileset_params.rect_to_draw_on_map.x -= tileset_params.tile_size;
    }

    // If new_x == old_x and new_y < old_y :  change size of selection 0/+1 AND Change origin 0/-1
    else if (new_top_left.x == old_top_left.x && new_top_left.y < old_top_left.y) {
        this->tileset_params.selection_size.y += 1;
        this->tileset_params.rect_to_draw_on_map.y -= tileset_params.tile_size;
    }

    // If new_x < old_x and new_y > old_y :  change size of selection +1/+1 AND Change origin -1/0
    else if (new_top_left.x < old_top_left.x && new_top_left.y > old_top_left.y) {
        this->tileset_params.selection_size.x += 1;
        this->tileset_params.selection_size.y += 1;
        this->tileset_params.rect_to_draw_on_map.x -= tileset_params.tile_size;
    }

    // If new_x > old_x and new_y < old_y :  change size of selection +1/+1 AND Change origin 0/-1
    else if (new_top_left.x > old_top_left.x && new_top_left.y < old_top_left.y) {
        this->tileset_params.selection_size.x += 1;
        this->tileset_params.selection_size.y += 1;
        this->tileset_params.rect_to_draw_on_map.y -= tileset_params.tile_size;
    }

    tileset_params.rect_to_draw_on_map.w = tileset_params.tile_size * tileset_params.selection_size.x;
    tileset_params.rect_to_draw_on_map.h = tileset_params.tile_size * tileset_params.selection_size.y;
}

void Editor::handleMapLeftClick() {
    // Avoid endlessly resetting the same map tile to the same tileset tile
    if (this->status.current_status == Status::DRAGGING && !mouseIsInNewTile(this->mouse_coord.old_coord, this->mouse_coord.new_coord)) {
        return;
    }

    sf::Vector2<int> new_pos = Tools::getTopLeft(this->mouse_coord.new_coord, tileset_params.tile_size);

    Rectangle dest(new_pos.x, new_pos.y,
                   tileset_params.tile_size * tileset_params.selection_size.x,
                   tileset_params.tile_size * tileset_params.selection_size.y);

    this->map.updateTiles(dest, tileset_params.rect_to_draw_on_map, tileset_params.tile_size);
}

bool Editor::mouseIsInNewTile(sf::Vector2<int> old_coord, sf::Vector2<int> new_coord) const {
    sf::Vector2<int> old_top_left = Tools::getTopLeft(old_coord, tileset_params.tile_size);
    sf::Vector2<int> new_top_left = Tools::getTopLeft(new_coord, tileset_params.tile_size);

    return (old_top_left.x != new_top_left.x || old_top_left.y != new_top_left.y);
}