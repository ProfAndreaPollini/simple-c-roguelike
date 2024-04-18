//
// Created by profa on 18/04/2024.
//

#ifndef EXAMPLE_TILE_LIST_H
#define EXAMPLE_TILE_LIST_H

#include <stdbool.h>
#include "tile.h"

#include "raylib.h"
#include "entity.h"

typedef struct TileListNode {
    Tile *tile;
    Vector2Int position;
    struct TileListNode *next;
} TileListNode;

typedef struct TileList {
    TileListNode *head;
} TileList;

typedef struct TileListIterator {
    TileListNode *current;
    TileList *list;
} TileListIterator;

TileList *tile_list_create();
void tile_list_add(TileList *list, Tile *tile, Vector2Int position);
void tile_list_clear(TileList *list, bool destroy_tiles);
int tile_list_count(TileList *list);

TileListIterator tile_list_iterator(TileList *list);
Tile *tile_list_next(TileListIterator *iterator);
void tile_list_iter_destroy(TileListIterator *list);
TileListNode* tile_list_choose_random(TileListIterator *list);

#endif //EXAMPLE_TILE_LIST_H
