//
// Created by profa on 18/04/2024.
//

#include <stdlib.h>
#include "../include/entity_list.h"

EntityList *entity_list_create() {
    EntityList *list = (EntityList*) malloc(sizeof(EntityList));
    list->head = NULL;
    return list;
}

void entity_list_add(EntityList *list, Entity *entity) {
    EntityListNode *node = (EntityListNode*) malloc(sizeof(EntityListNode));
    node->entity = entity;
    node->next = list->head;
    list->head = node;
}

void entity_list_clear(EntityList *list, bool destroy_entities) {
    EntityListNode *node = list->head;
    while (node != NULL) {
        EntityListNode *next = node->next;
        if (destroy_entities) {
            entity_destroy(node->entity);
        }
        free(node);
        node = next;
    }
    list->head = NULL;
}

int entity_list_count(EntityList *list) {
    int count = 0;
    EntityListNode *node = list->head;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

EntityListIterator entity_list_iterator(EntityList *list) {
    EntityListIterator result;
    result.list = list;
    return result;
}

Entity *entity_list_next(EntityListIterator *iterator) {
    if (iterator->current == NULL) {
        iterator->current = iterator->list->head;
    } else {
        iterator->current = iterator->current->next;
    }
    if (iterator->current != NULL) {
        return iterator->current->entity;
    }
    return NULL;
}
