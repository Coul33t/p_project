#include "map_maker/include/editor.h"

int main() {
    Editor editor;
    editor.init(1280, 720, 16);
    editor.open();
    editor.loadTileset("../res/tilesets/gold_and_silver/tileset.png");
    editor.run();
    return 0;
}