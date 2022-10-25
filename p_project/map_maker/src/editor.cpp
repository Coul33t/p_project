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
}

void Editor::open() const {
    InitWindow(this->params.size.w, this->params.size.h, "Map Editor");
    SetTargetFPS(30);
}

void Editor::loadTileset(const std::string& path) {
    this->tileset = LoadTexture(path.c_str());
    this->tileset_params.size.w = this->tileset.width;
    this->tileset_params.size.h = this->tileset.height;

    this->tileset_params.rect_to_draw.x = 0;
    this->tileset_params.rect_to_draw.y = 0;
    this->tileset_params.rect_to_draw.width = this->tileset.width;
    this->tileset_params.rect_to_draw.height = this->params.size.h;
}

void Editor::run() {
    //TODO: see RenderTexture for caching
    tileset_params.pos.x = this->params.size.w - this->tileset.width;
    tileset_params.pos.y = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        handleInput();

        ClearBackground(WHITE);

        DrawTextureRec(this->tileset,
                       this->tileset_params.rect_to_draw,
                       this->tileset_params.pos,
                       Color(WHITE));

        DrawText("0, 0", 0, 0, 20, LIGHTGRAY);
        DrawText("100, 100", 100, 100, 20, LIGHTGRAY);
        DrawText("200, 0", 200, 0, 20, LIGHTGRAY);
        DrawText("0, 200", 0, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    UnloadTexture(this->tileset);
    CloseWindow();
}

void Editor::handleInput() {
    Vector2 mouse_pos = GetMousePosition();

    float new_offset = 0.0;

    // Tileset
    if (Tools::isInRectangle(mouse_pos,
                             params.size.w - tileset_params.size.w, 0,
                             tileset_params.size.w, tileset_params.size.h)) {

        // Tileset scrolling
        new_offset = (GetMouseWheelMove() * params.scroll_speed);

        if (new_offset != 0.0) {
            tileset_params.rect_to_draw.y -= new_offset * tileset_params.tile_size;
        }

        // Tile selection
        // TODO: do
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 tileset_pos;
            tileset_pos.x = mouse_pos.x - (params.size.w - tileset_params.size.w);
            tileset_pos.y = tileset_params.rect_to_draw.y + mouse_pos.y;
        }
    }
}