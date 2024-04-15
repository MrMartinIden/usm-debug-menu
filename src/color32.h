#pragma once

#include <cstdint>

struct color32
{
    uint8_t field_0[4];

    void set_alpha(uint8_t a2) {
        this->field_0[3] = a2;
    }
};
