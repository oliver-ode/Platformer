#pragma once

#include "../types.h"

enum Hit : EntityHit {
    TopHit = 1,
    BottomHit = 2,
    LeftHit = 4,
    RightHit = 8,
};

enum Movement : MovementState {
    Idle = 1,
    Run = 2,
    Jumping = 4,
    Falling = 8,
    Crouching = 16,
};