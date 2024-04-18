//
// Created by profa on 17/04/2024.
//

#ifndef EXAMPLE_ENTITY_H
#define EXAMPLE_ENTITY_H

#include "raylib.h"

enum sprites {
    PLAYER_SPRITE = 27
};
typedef enum sprites sprites_t;

typedef struct Vector2Int {
    int x;
    int y;
} Vector2Int;

struct entity {
    int x;
    int y;
    int health;
    int max_health;
    sprites_t sprite;
};
typedef struct entity Entity;

Entity *entity_create(int x, int y, sprites_t sprite, int max_health);
void entity_move(Entity *entity, Vector2Int direction);
void entity_destroy(Entity *entity);
void entity_draw(Entity *e, Texture2D *spritesTexture, bool draw_shadow);

#endif //EXAMPLE_ENTITY_H
