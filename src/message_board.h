#pragma once

#include "color32.h"
#include "float.hpp"

#include <vector>

struct message_board {
    struct internal {
        char field_0[100];
        float field_64;
        color32 field_68 {};
    };

    std::vector<internal> field_0;

    message_board() = default;

    struct string {
        int field_0;
        int field_4;
        char *guts;
        void *field_C;
    };

    void post(string a1, Float a2, color32 a3);

    void frame_advance(float a2);

    void render();
};

extern void message_board_patch();
