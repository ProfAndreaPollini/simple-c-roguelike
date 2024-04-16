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

#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 1600;
int screenHeight = 900;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

Texture2D spritesTexture;



// constants
#define SCALE 2.0f
#define CELLS_X 49
#define CELLS_Y 30
#define SPRITESHET_WIDTH 49
#define SPRITESHET_HEIGHT 30


enum cell_type {
    CELL_EMPTY = -1,
    CELL_WALL = 637,
    CELL_TREE1 = 50,

    CELL_ENEMY = 34,
    CELL_GEM = 4,
    CELL_POTION = 5,
    CELL_KEY = 6,
    CELL_DOOR = 7,
    CELL_MAX
};
typedef enum cell_type cell_type_t;

enum sprites {
    PLAYER_SPRITE = 27
};
typedef enum sprites sprites_t;

struct entity {
    int x;
    int y;
    sprites_t sprite;
};
typedef struct entity entity_t;

// variables
cell_type_t cells[CELLS_X *CELLS_Y];
entity_t player = { 10, 10, PLAYER_SPRITE };
float timer = 0.0f;

entity_t enemies[10];
// functions

void set_cell(int x, int y, cell_type_t value) {
    if (x >= 0 && x < CELLS_X && y >= 0 && y < CELLS_Y) {
        cells[y * CELLS_X + x] = value;
    }
}

cell_type_t get_cell(int x, int y) {
    if (x >= 0 && x < CELLS_X && y >= 0 && y < CELLS_Y) {
        return cells[y * CELLS_X + x];
    }
    return 0;
}


void init_enemies() {
    for (int i = 0; i < 10; i++) {
        enemies[i].x = GetRandomValue(0, CELLS_X - 1);
        enemies[i].y = GetRandomValue(0, CELLS_Y - 1);
        enemies[i].sprite = CELL_ENEMY;
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
    timer = 0.1f;
    for (int i = 0; i < CELLS_X * CELLS_Y; i++) {
        cells[i] = CELL_WALL;
    }

    set_cell(0, 0, CELL_TREE1);

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
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void draw_entity(entity_t e,bool draw_shadow) {
    int sprite_x = e.sprite % SPRITESHET_WIDTH;
    int sprite_y = e.sprite / SPRITESHET_WIDTH;
    Rectangle source = { sprite_x*16, sprite_y*16, 16, 16 };
    Rectangle dest = { e.x * 16 * SCALE, e.y * 16 * SCALE, 16 * SCALE, 16 * SCALE };
    if (draw_shadow) {
        DrawRectangle(e.x * 16 * SCALE, e.y * 16 * SCALE, 16 * SCALE, 16 * SCALE, (Color){0, 0, 0, 128});
    }

    DrawTexturePro(spritesTexture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
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
    timer-= GetFrameTime();

    if (timer <= 0) {
        timer = 0.1f;
        // Get input

        if (IsKeyDown(KEY_RIGHT)) {
            player.x++;
        }
        if (IsKeyDown(KEY_LEFT)) {
            player.x--;
        }
        if (IsKeyDown(KEY_DOWN)) {
            player.y++;
        }
        if (IsKeyDown(KEY_UP)) {
            player.y--;
        }
    }


    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(DARKGRAY);
//    DrawTextureEx(spritesTexture, (Vector2){0, 0}, 0.0f, SCALE, WHITE);
//    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    for (int y = 0; y < CELLS_Y; y++) {
        for (int x = 0; x < CELLS_X; x++) {
            int cell = get_cell(x, y);
            if (cell >= 0) {
                draw_tile(x, y, cell);
            }
        }
    }

    // draw player
    draw_entity(player,true);

    // draw enemies
    for (int i = 0; i < 10; i++) {
        draw_entity(enemies[i],true);
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
}