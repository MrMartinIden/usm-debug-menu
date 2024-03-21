#pragma once

#include "float.hpp"

#include <cstdint>

struct string_hash;

struct animation_controller {
    struct anim_ctrl_handle {
        int field_0;
        int field_4;
        struct {
            int m_vtbl;
        } * field_8;

        void set_anim_speed(Float a2);
    };

    anim_ctrl_handle play_base_layer_anim(
            const string_hash &a3,
            Float a4,
            uint32_t a5,
            bool a6);
};
