#pragma once

#include "entity.h"

#include "string_hash.h"
#include "animation_controller.h"
#include "nal_system.h"
#include "resource_key.h"
#include "resource_pack_slot.h"
#include "vector3d.h"

#include <vector>

struct nalAnyPose;
struct nalBaseSkeleton;

template<typename T>
struct nalAnimClass;

struct ai_player_controller;
struct damage_interface;
struct physical_interface;

struct actor : entity
{
    damage_interface *m_damage_interface;
    physical_interface *m_physical_interface;
    nalBaseSkeleton *m_skeleton;
    animation_controller *anim_ctrl;
    void *adv_ptrs;
    void *field_7C;
    void *m_interactable_ifc;
    void *m_facial_expression_interface;
    int field_88;
    ai_player_controller *m_player_controller;
    char field_90[0xC];
    uint8_t *field_9C;
    void *field_A0;
    int16_t field_A4;
    int16_t field_A6;
    int16_t field_A8[1];
    int16_t field_AA;
    vector3d field_AC;
    int field_B8;
    resource_pack_slot *field_BC;

    ai_player_controller *get_player_controller() {
        return this->m_player_controller;
    }

    physical_interface *physical_ifc()
    {
        physical_interface * (__fastcall *func)(void *) = bit_cast<decltype(func)>(0x004B8B40);
        return func(this);
    }

    void allocate_anim_controller(unsigned int a2, nalBaseSkeleton *a3) {
        void (__fastcall *func)(void *, int, uint32_t, nalBaseSkeleton *) = 
            bit_cast<decltype(func)>(0x004CC630);
        func(this, 0, a2, a3);
    }

    animation_controller::anim_ctrl_handle play_anim(const string_hash &a3);

    static std::vector<nalAnimClass<nalAnyPose> *> get_animations(actor *a1);
};
