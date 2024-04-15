#pragma once

#include "bit.h"
#include "vector3d.h"

struct po
{
    float m[4][4];

    vector3d &get_z_facing() const {
        return *bit_cast<vector3d *>(&this->m[2]);
    }
};
