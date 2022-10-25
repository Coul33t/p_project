//
// Created by couland-q on 25/10/22.
//

#ifndef P_PROJECT_EDITOR_H
#define P_PROJECT_EDITOR_H

#include <string>
#include <iostream>

#include <raylib.h>

#include "../../game/include/map.h"
#include "../../tools/include/tools.h"
#include "params.h"
#include "constants.h"

class Editor {
public:
    Editor();
    ~Editor();

    void init(int w = 640, int h = 320, int tile_size = 8);
    void open() const;
    void run();

    void loadTileset(const std::string& path);

    void handleInput();


    EditorParams params;
    TilesetParams tileset_params;

    Map map;
    Texture2D tileset;
};

#endif //P_PROJECT_EDITOR_H
