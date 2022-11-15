//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_EDITOR_H
#define P_PROJECT_EDITOR_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../../common/include/map.h"
#include "../../tools/include/tools.h"
#include "../../common/include/sprite.h"
#include "params.h"
#include "constants.h"

enum Status {NONE, DRAGGING};

struct EditorStatus {
    Status current_status, last_status;

    EditorStatus() {
        current_status = Status::NONE;
        last_status = Status::NONE;
    }

    void update() {
        this->last_status = current_status;
    }

    bool sameAsLast() {
        return (this->last_status == this->current_status);
    }
};

struct MouseCoord {
    sf::Vector2<int> old_coord;
    sf::Vector2<int> new_coord;
};

class Editor {
public:
    Editor();
    ~Editor();

    void init(int w = 640, int h = 320, int tile_size = 16);
    void initMap(int w = 128, int h = 64);
    void open() const;
    void run();

    void drawOverlayingShapes();

    bool loadTileset(const std::string& path);

    void handleEvent(sf::Event e);
    void handleMouseInput(sf::Event e);

    bool mouseIsInNewTile(sf::Vector2<int> old_coord, sf::Vector2<int> new_coord) const;

    EditorParams params;
    TilesetParams tileset_params;

    sf::RenderWindow window;

    Map map;
    Sprite tileset;
    EditorStatus status;
    MouseCoord mouse_coord;
};

#endif //P_PROJECT_EDITOR_H
