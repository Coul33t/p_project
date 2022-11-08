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


    EditorParams params;
    TilesetParams tileset_params;

    sf::RenderWindow window;

    Map map;
    Sprite tileset;
};

#endif //P_PROJECT_EDITOR_H
