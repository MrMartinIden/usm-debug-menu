#pragma once

#include "string_hash.h"

struct actor;
struct param_block;

namespace ai {

struct ai_core;

struct info_node {
    int m_vtbl;
    string_hash field_4;
    ai_core *field_8;
    actor *field_C;
    param_block m_param_block;
};

}
