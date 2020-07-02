#pragma once

#include <array>
#include "../../common/network/constants.h"
#include "../../common/types.h"
#include <glm/glm.hpp>

namespace client{
    struct Entity{
        glm::vec2 pos;
        u8 alive;

        u8 animationTick; // What frame of animation the player is on
        float movementSpeed; // Movement speed of the player
        float jumpHeight; // Jump height of the player
        u8 hitted; // What the player is hitting (N/A, N/A, N/A, N/A, right, left, bottom, top)
        u8 state; // What state the player is in (N/A, N/A, N/A, crouching, falling, jumping, run, idle)
    };
    using EntityArray = std::array<Entity, ENTITY_COUNT>;
}