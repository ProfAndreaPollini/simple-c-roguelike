//
// Created by profa on 17/04/2024.
//

#include "gamemap.h"
#include <stdlib.h>

GameMap *gamemap_create(int width, int height) {
    GameMap *map = (GameMap*) malloc(sizeof(GameMap));
    map->width = width;
    map->height = height;
    map->cells = (cell_type_t*) malloc(sizeof(cell_type_t) * width * height);
    for (int i = 0; i < width * height; i++) {
        map->cells[i] = CELL_EMPTY;
    }
    return map;
}

void gamemap_destroy(GameMap *map) {
    free(map->cells);
    free(map);
}

void gamemap_set_cell(GameMap *map, int x, int y, cell_type_t value) {
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        map->cells[y * map->width + x] = value;
    }
}

cell_type_t gamemap_get_cell(GameMap *map, int x, int y) {
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        return map->cells[y * map->width + x];
    }
    return CELL_EMPTY;
}


