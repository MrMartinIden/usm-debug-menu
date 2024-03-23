#pragma once

#include "string_hash.h"

struct script_object;

struct vm_executable {
    script_object *owner;
    string_hash fullname;
    string_hash name;
    int parms_stacksize;

    auto get_parms_stacksize() const
    {
        return this->parms_stacksize;
    }
};

