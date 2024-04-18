//
// Created by profa on 17/04/2024.
//

#include "gamemap.h"
#include "raylib.h"
#include <stdlib.h>

GameMap *gamemap_create(int width, int height) {
    GameMap *map = (GameMap*) malloc(sizeof(GameMap));
    map->width = width;
    map->height = height;
    map->cells = (Tile *) malloc(sizeof(Tile) * width * height);
    for (int i = 0; i < width * height; i++) {
        map->cells[i].type = CELL_EMPTY;
    }
    return map;
}

void gamemap_destroy(GameMap *map) {
    free(map->cells);
    free(map);
}

void gamemap_set_cell(GameMap *map, int x, int y, cell_type_t value) {
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        map->cells[y * map->width + x].type = value;
    }
}

Tile* gamemap_get_cell(GameMap *map, int x, int y) {
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        return &map->cells[y * map->width + x];
    }
    return NULL;
}

GameMap *gamemap_apply_random_walk(GameMap *map, int steps, int n_walkers, int start_x, int start_y) {
    int x = start_x;
    int y = start_y;
    for (int i = 0; i < n_walkers; i++) {
        for (int j = 0; j < steps; j++) {
            int direction = GetRandomValue(0, 3);
            switch (direction) {
                case 0: // up
                    y -= 1;
                    break;
                case 1: // down
                    y += 1;
                    break;
                case 2: // left
                    x -= 1;
                    break;
                case 3: // right
                    x += 1;
                    break;
            }
            gamemap_set_cell(map, x, y, CELL_FLOOR);
        }
    }
    return map;
}

TileListIterator gamemap_get_tiles_by_type(GameMap *map, cell_type_t type) {
    TileList *list = tile_list_create();
    for (int i = 0; i < map->width * map->height; i++) {
        if (map->cells[i].type == type) {
            Tile *tile = &map->cells[i];
            tile_list_add(list, tile, (Vector2Int){i % map->width, i / map->width});
        }
    }
    return tile_list_iterator(list);
}




