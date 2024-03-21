#pragma once

#include "mvector.h"
#include "param_block.h"
#include "variable.h"

#include "list.hpp"

struct actor;

namespace ai {

struct info_node;

struct ai_core {
    char field_0[0x50];
    param_block field_50;
    int field_5C;
    mVector<ai::info_node> *field_60;
    actor *field_64;

    param_block * get_param_block()
    {
        return &this->field_50;
    }

    actor * get_actor(int) {
        return field_64;
    }

    static inline Var<_std::list<ai_core *> *> the_ai_core_list_high {0x0096BE24};

};


}
