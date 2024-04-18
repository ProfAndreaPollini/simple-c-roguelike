//
// Created by profa on 18/04/2024.
//

#ifndef EXAMPLE_ENTITY_LIST_H
#define EXAMPLE_ENTITY_LIST_H

#include <stdbool.h>
#include "entity.h"

typedef struct EntityListNode {
    Entity *entity;
    struct EntityListNode *next;
} EntityListNode;

typedef struct EntityList {
    EntityListNode *head;
//    EntityListNode *tail;
} EntityList;

typedef struct EntityListIterator {
    EntityListNode *current;
    EntityList *list;
} EntityListIterator;

EntityList *entity_list_create();
void entity_list_add(EntityList *list, Entity *entity);
void entity_list_clear(EntityList *list, bool destroy_entities);
int entity_list_count(EntityList *list);

EntityListIterator entity_list_iterator(EntityList *list);
Entity *entity_list_next(EntityListIterator *iterator);

#endif //EXAMPLE_ENTITY_LIST_H
