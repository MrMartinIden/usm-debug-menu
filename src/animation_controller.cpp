#include "animation_controller.h"

#include "bit.h"

#include <cstdio>

animation_controller::anim_ctrl_handle animation_controller::play_base_layer_anim(
        const string_hash &a3,
        Float a4,
        uint32_t a5,
        bool a6)
{
    printf("animation_controller::play_base_layer_anim\n");

    animation_controller::anim_ctrl_handle result;
    void (__fastcall *func)(void *, int, animation_controller::anim_ctrl_handle *, const string_hash *, Float, uint32_t, bool) = bit_cast<decltype(func)>(0x0049B9A0);
    func(this, 0, &result, &a3, a4, a5, a6);

    return result;
}

void animation_controller::anim_ctrl_handle::set_anim_speed(Float a2)
{
    printf("animation_controller::anim_ctrl_handle::set_anim_speed\n");

    struct {
        char field_0[0x58];
        void (__fastcall *field_58)(void *, int, Float);
        void (__fastcall *field_5C)(void *, int, Float, Float);
    } * vtbl = bit_cast<decltype(vtbl)>(this->field_8->m_vtbl);

    if ( this->field_0 ) {
        vtbl->field_58(this->field_8, 0, a2);
    } else {
        vtbl->field_5C(
            this->field_8,
            0,
            a2,
            this->field_4);
    }
};
