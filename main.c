//
// Created by profa on 16/04/2024.
//

/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB and PLATFORM_DESKTOP
*   As you will notice, code structure is slightly different to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdlib.h>
#include "raylib.h"
#include "timer.h"
#include "include/entity.h"
#include "constants.h"
#include "gamemap.h"
#include "include/entity_list.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame


Texture2D spritesTexture;


// variables

GameMap* game_map;
Entity* player;
Timer* timer;
EntityList* enemies_list;


void init_enemies() {
    enemies_list = entity_list_create();
    TileListIterator it = gamemap_get_tiles_by_type(game_map, CELL_FLOOR);


    for (int i = 0; i < 10; i++) {

        TileListNode* node = tile_list_choose_random(&it);
        Entity *enemy = entity_create(node->position.x,node->position.y, CELL_ENEMY, 100);
        entity_list_add(enemies_list, enemy);
    }
}

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Image image = LoadImage(ASSETS_PATH "sprites.png");     // Loaded in CPU memory (RAM)
    spritesTexture = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    game_map = gamemap_create(CELLS_X, CELLS_Y);
    player = entity_create(10, 10, PLAYER_SPRITE,100);

    timer = timer_create(0.1f, 0.0f, true);
    for (int i = 0; i < CELLS_X * CELLS_Y; i++) {
        gamemap_set_cell(game_map, i % CELLS_X, i / CELLS_X, CELL_WALL);
    }

    gamemap_apply_random_walk(game_map, 100, 10, 10, 10);
    TileListIterator it = gamemap_get_tiles_by_type(game_map, CELL_FLOOR);

    TileListNode* node = tile_list_choose_random(&it);

    if (node != NULL) {
        player->x = node->position.x;
        player->y = node->position.y;
    }

    gamemap_set_cell(game_map, 1, 1, CELL_TREE1);

    init_enemies();
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    gamemap_destroy(game_map);
    timer_destroy(timer);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void draw_tile(int x, int y, int tile) {
    int tile_x = tile % SPRITESHET_WIDTH;
    int tile_y = tile / SPRITESHET_WIDTH;
    Rectangle source = { tile_x*16, tile_y*16, 16, 16 };
    Rectangle dest = { x * 16 * SCALE, y * 16 * SCALE, 16 * SCALE, 16 * SCALE };
    DrawTexturePro(spritesTexture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    timer_update(timer, -GetFrameTime());


    if (timer_expired(timer)) {

        // Get input
        Vector2Int movement = {0, 0};

        if (IsKeyDown(KEY_RIGHT)) {
            movement.x = 1;
        }
        if (IsKeyDown(KEY_LEFT)) {
            movement.x = -1;
        }
        if (IsKeyDown(KEY_DOWN)) {
            movement.y = 1;
        }
        if (IsKeyDown(KEY_UP)) {
            movement.y = -1;
        }

        if (movement.x != 0 || movement.y != 0) {
            Vector2Int new_pos = {player->x + movement.x, player->y + movement.y};
            if (!IS_SOLID_CELL(gamemap_get_cell(game_map, new_pos.x, new_pos.y)->type)) {
                entity_move(player, movement);
            } else {
                TraceLog(LOG_INFO, "Collision");
            }


        }
    }


    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    player->health -= 1;
    if (player->health <= 0) {
        player->health = player->max_health;
    }
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(DARKGRAY);

    for (int y = 0; y < CELLS_Y; y++) {
        for (int x = 0; x < CELLS_X; x++) {
            Tile* cell = gamemap_get_cell(game_map, x, y);
            if (cell >= 0) {
                draw_tile(x, y, cell->type);
            }
        }
    }

    // draw player
    entity_draw(player, &spritesTexture, true);


    EntityListNode* current = enemies_list->head;
    while (current != NULL) {
        entity_draw(current->entity, &spritesTexture, true);
        current = current->next;
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
}