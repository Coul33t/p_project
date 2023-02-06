#include <iostream>
#include "map_maker/include/editor.h"
#include "examples/multiple_windows.h"
#include "examples/imgui_sfml_example.h"
#include "examples/imgui_test.h"
int main() {
    //ImgGuiSFMLMultipleWindows::test();
    //ImGuiSFMLExample::test();
    ImGuiTest::test();
    /*Editor editor;
    editor.init(1280, 720, 16);
    editor.initMap(128, 64);

    if (!editor.loadTileset("../res/tilesets/gold_and_silver/tileset.png")) {
        return 1;
    }

    editor.run();*/
    return 0;
}