//
// Created by profa on 17/04/2024.
//

#include "timer.h"
#include "raylib.h"
#include "entity.h"
#include "constants.h"

#include <stdlib.h>

void entity_move(Entity *entity, Vector2Int direction) {
    entity->x += direction.x;
    entity->y += direction.y;
}

Entity *entity_create(int x, int y, sprites_t sprite,int max_health) {
    Entity *entity = (Entity*) malloc(sizeof(Entity));
    entity->x = x;
    entity->y = y;
    entity->sprite = sprite;
    entity->health = max_health;
    entity->max_health = max_health;
    return entity;
}

void entity_destroy(Entity *entity) {
    free(entity);
}

void entity_draw(Entity *e, Texture2D *spritesTexture, bool draw_shadow) {
    int sprite_x = e->sprite % SPRITESHET_WIDTH;
    int sprite_y = e->sprite / SPRITESHET_WIDTH;
    Rectangle source = {sprite_x * 16, sprite_y * 16, 16, 16};
    Rectangle dest = {e->x * 16 * SCALE, e->y * 16 * SCALE, 16 * SCALE, 16 * SCALE};
    if (draw_shadow) {
        DrawRectangle(e->x * 16 * SCALE, e->y * 16 * SCALE, 16 * SCALE, 16 * SCALE, (Color) {0, 0, 0, 128});
    }

    DrawTexturePro(*spritesTexture, source, dest, (Vector2) {0, 0}, 0.0f, WHITE);

    // draw health bar below entity
    float health_ratio = (float) e->health / e->max_health;
    DrawRectangle(e->x * 16 * SCALE, e->y * 16 * SCALE + 18 * SCALE, 16 * SCALE, 4 * SCALE, (Color) {255, 0, 0, 128});
    DrawRectangle(e->x * 16 * SCALE, e->y * 16 * SCALE + 18 * SCALE, 16*health_ratio * SCALE, 4 * SCALE, (Color) {0, 255, 0, 255});
}
