#pragma once

#include <array>
#include "../../common/network/constants.h"
#include "../../common/types.h"
#include <glm/glm.hpp>

namespace client{
    struct Entity{
        glm::vec2 pos;

        u8 alive;
    };
    using EntityArray = std::array<Entity, ENTITY_COUNT>;
}