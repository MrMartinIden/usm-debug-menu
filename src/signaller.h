#pragma once

#include "entity_base.h"

#include "common.h"

struct signaller : entity_base {
    int field_44;
};

VALIDATE_SIZE(signaller, 0x48u);
