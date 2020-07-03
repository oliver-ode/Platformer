#pragma once

#include <array>
#include "../../common/types.h"
#include <glm/glm.hpp>

namespace server{
    struct Entity {
        glm::vec2 pos;
        Entity *p_target = nullptr;
        glm::vec2 targetPoint;
        glm::vec2 velocity{0.0f};

        u8 alive = 0;

        float movementSpeed; // Movement speed of the player
        float jumpHeight; // Jump height of the player
        u8 hitted; // What the player is hitting (N/A, N/A, N/A, N/A, right, left, bottom, top)
        
        u8 animationTick; // What frame of animation the player is on
        u8 state; // What state the player is in (N/A, N/A, N/A, crouching, falling, jumping, run, idle)
    };
    using EntityArray = std::array<Entity, ENTITY_COUNT>;
}