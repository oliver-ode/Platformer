#pragma once

#include "../types.h"

enum Hit : EntityHit {
    Top = 1,
    Bottom = 2,
    Left = 4,
    Right = 8,
};

enum Movement : MovementState {
    Idle = 1,
    Run = 2,
    Jumping = 4,
    Falling = 8,
    Crouching = 16,
};