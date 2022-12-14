#include <iostream>
#include "map_maker/include/editor.h"

int main() {
    Editor editor;
    editor.init(1280, 720, 16);
    editor.initMap(128, 64);

    if (!editor.loadTileset("../res/tilesets/gold_and_silver/tileset.png")) {
        return 1;
    }

    editor.run();
    return 0;
}