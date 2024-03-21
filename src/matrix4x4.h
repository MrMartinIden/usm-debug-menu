#pragma once

#include "vector4d.h"

struct matrix4x4 {
    vector4d arr[4];

    auto &operator[](uint32_t idx) {
        return arr[idx];
    }
};
