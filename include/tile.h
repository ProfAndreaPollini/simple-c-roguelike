//
// Created by profa on 18/04/2024.
//

#ifndef EXAMPLE_TILE_H
#define EXAMPLE_TILE_H

enum cell_type {
    CELL_EMPTY = -1,
    CELL_WALL = 637,
    CELL_TREE1 = 50,

    CELL_ENEMY = 34,
    CELL_FLOOR = 16,
    CELL_GEM = 4,
    CELL_POTION = 5,
    CELL_KEY = 6,
    CELL_DOOR = 7,
    CELL_MAX
};
typedef enum cell_type cell_type_t;

typedef struct Tile {
    cell_type_t type;
} Tile;

#endif //EXAMPLE_TILE_H
