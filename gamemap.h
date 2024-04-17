//
// Created by profa on 17/04/2024.
//

#ifndef EXAMPLE_GAMEMAP_H
#define EXAMPLE_GAMEMAP_H

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

#define IS_SOLID_CELL(cell) (cell == CELL_WALL || cell == CELL_TREE1)

typedef struct GameMap {
    cell_type_t *cells;
    int width;
    int height;
} GameMap;

GameMap *gamemap_create(int width, int height);
void gamemap_destroy(GameMap *map);
void gamemap_set_cell(GameMap *map, int x, int y, cell_type_t value);
cell_type_t gamemap_get_cell(GameMap *map, int x, int y);



#endif //EXAMPLE_GAMEMAP_H
