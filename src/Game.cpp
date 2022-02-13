#include "Game.hpp"
#include "Rendering.hpp"
#include "Vector2.hpp"


struct Entity {
    Vector2 position;
    Vector2 half_size;
    Vector2 velocity;
    u32 color;
};


constexpr s32 MAX_ENTITIES = 8;
static s32 num_entities = 0;
static Entity entities[MAX_ENTITIES];


static void
AddEntity(Entity entity) {
    if (num_entities < MAX_ENTITIES) {
        entities[num_entities] = entity;
        num_entities += 1;
    }
}

void InitGame() {
    Entity player;
    player.position = { -8.0f, 0.0f };
    player.half_size = { 0.2f, 1.0f };
    player.velocity = { 0.0f, 0.0f };
    player.color = 0x3333dd;
    AddEntity(player);

    Entity ai;
    ai.position = -player.position;
    ai.half_size = player.half_size;
    ai.velocity = player.velocity;
    ai.color = 0xdd3333;
    AddEntity(ai);

    Entity ball;
    ball.position = { 0.0f, 0.0f };
    ball.half_size = { 0.2f, 0.2f };
    ball.velocity = { -2.0f, -3.5f };
    ball.color = 0xffffff;
    AddEntity(ball);
}

void UpdateGame(Input input, f32 delta_time) {
    for (int i = 0; i < num_entities; ++i) {
        Entity *entity = &entities[i];

        // Update position
        entity->position += entity->velocity * delta_time;

        // Check for collisions with northern and southern walls
        constexpr f32 SCREEN_HALF_HEIGHT = (1.0f / RENDER_SCALE) * 0.5f;
        if (((entity->position.y + entity->half_size.y) >= SCREEN_HALF_HEIGHT) ||
            ((entity->position.y - entity->half_size.y) <= -SCREEN_HALF_HEIGHT)) {
            entity->velocity.y *= -1;
        }
    }
}

void RenderGame(Buffer buffer) {
    DrawRectInPixels(buffer, 0, 0, buffer.width, buffer.height, 0x000000);
    for (int i = 0; i < num_entities; ++i) {
        Entity entity = entities[i];
        DrawRect(buffer,
            entity.position.x, entity.position.y,
            entity.half_size.x, entity.half_size.y,
            entity.color
        );
    }
}

