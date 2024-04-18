//
// Created by profa on 18/04/2024.
//

#include <malloc.h>
#include "../include/tile_list.h"

TileList *tile_list_create() {
    TileList *list = (TileList*) malloc(sizeof(TileList));
    list->head = NULL;
    return list;
}

void tile_list_add(TileList *list, Tile *tile, Vector2Int position ) {
    TileListNode *node = (TileListNode*) malloc(sizeof(TileListNode));
    node->tile = tile;
    node->position = position;
    node->next = list->head;
    list->head = node;
}

void tile_list_clear(TileList *list, bool destroy_tiles) {
    TileListNode *node = list->head;
    while (node != NULL) {
        TileListNode *next = node->next;
        if (destroy_tiles) {
            free(node->tile);
        }
        free(node);
        node = next;
    }
    list->head = NULL;
}

int tile_list_count(TileList *list) {
    int count = 0;
    TileListNode *node = list->head;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

TileListIterator tile_list_iterator(TileList *list) {
    TileListIterator result;
    result.list = list;
    return result;
}

Tile *tile_list_next(TileListIterator *iterator) {
    if (iterator->current == NULL) {
        iterator->current = iterator->list->head;
    } else {
        iterator->current = iterator->current->next;
    }
    if (iterator->current != NULL) {
        return iterator->current->tile;
    }
    return NULL;
}

TileListNode *tile_list_choose_random(TileListIterator *it) {
    int count = tile_list_count(it->list);
    if (count == 0) {
        return NULL;
    }
    int index = GetRandomValue(0, count - 1);
    TileListNode *node = it->list->head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}


void tile_list_iter_destroy(TileListIterator *it) {
    free(it->list);
    free(it);
}
