//
// Created by profa on 17/04/2024.
//

#ifndef EXAMPLE_GAMEMAP_H
#define EXAMPLE_GAMEMAP_H



#include "tile.h"
#include "tile_list.h"

#define IS_SOLID_CELL(cell) (cell == CELL_WALL || cell == CELL_TREE1)

typedef struct GameMap {
    Tile *cells;
    int width;
    int height;
} GameMap;

GameMap *gamemap_create(int width, int height);
void gamemap_destroy(GameMap *map);
void gamemap_set_cell(GameMap *map, int x, int y, cell_type_t value);
Tile* gamemap_get_cell(GameMap *map, int x, int y);

GameMap *gamemap_apply_random_walk(GameMap *map, int steps, int n_walkers, int start_x, int start_y);

TileListIterator gamemap_get_tiles_by_type(GameMap *map, cell_type_t type);


#endif //EXAMPLE_GAMEMAP_H
