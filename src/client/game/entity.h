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
        u8 state; // What state the player is in (N/A, N/A, N/A, crouching, falling, jumping, run, idle)
    };
    using EntityArray = std::array<Entity, ENTITY_COUNT>;
}