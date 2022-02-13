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
    ball.velocity = { -3.5f, -4.5f };
    ball.color = 0xffffff;
    AddEntity(ball);
}

void UpdateGame(Input input, f32 delta_time) {
    // Process the input
    // TODO: We assume the player entity is at index 0
    constexpr f32 PLAYER_SPEED = 4.0f;
    Entity *player = &entities[0];
    if (IsButtonDown(input, BUTTON_W)) {
        player->velocity.y = PLAYER_SPEED;
    }
    else if (IsButtonDown(input, BUTTON_S)) {
        player->velocity.y = -PLAYER_SPEED;
    }
    else {
        player->velocity.y = 0.0f;
    }

    // Move the ai player
    // TODO: We assume the ai entity is at index 1
    //       and ball entity is at index 2
    Entity *ai = &entities[1];
    Entity *ball = &entities[2];
    if (ball->position.y > ai->position.y) {
        ai->velocity.y = PLAYER_SPEED;
    }
    else if (ball->position.y < ai->position.y) {
        ai->velocity.y =- PLAYER_SPEED;
    }
    else {
        ai->velocity.y = 0.0f;
    }
    
    // Check for collisions between ball and other entitites
    for (int j = 0; j < num_entities; ++j) {
        if (j == 2) {
            continue;
        }

        Entity *entity = &entities[j];
        if (ball->position.y <= (entity->position.y + entity->half_size.y) &&
            ball->position.y >= (entity->position.y - entity->half_size.y) &&
            ball->position.x <= (entity->position.x + entity->half_size.x) &&
            ball->position.x >= (entity->position.x - entity->half_size.x)) {

            ball->velocity.x *= -1;
        }
    }

    for (int i = 0; i < num_entities; ++i) {
        Entity *entity = &entities[i];

        // Update position
        entity->position += entity->velocity * delta_time;

        // Check for collisions with northern and southern walls
        constexpr f32 SCREEN_HALF_HEIGHT = (1.0f / RENDER_SCALE) * 0.5f;
        if (entity->position.y + entity->half_size.y >= SCREEN_HALF_HEIGHT) {
            entity->position.y = SCREEN_HALF_HEIGHT - entity->half_size.y;
            entity->velocity.y *= -1;
        }
        else if (entity->position.y - entity->half_size.y <= -SCREEN_HALF_HEIGHT) {
            entity->position.y = -SCREEN_HALF_HEIGHT + entity->half_size.y;
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

