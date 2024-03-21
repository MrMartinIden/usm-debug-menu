#pragma once

#include "common.h"
#include "entity_base_vhandle.h"
#include "string_hash.h"

#include <cstdint>

struct po;

struct conglomerate;
struct motion_effect_struct;
struct sound_and_pfx_interface;

struct entity_base {
    int m_vtbl;
    uint32_t field_4;
    uint32_t field_8;
    po *my_rel_po;
    string_hash field_10;
    po *my_abs_po;
    motion_effect_struct *field_18;
    entity_base_vhandle my_handle;
    entity_base *m_parent;
    entity_base *m_child;
    entity_base *field_28;
    int16_t proximity_map_cell_reference_count;
    uint8_t m_timer;
    void *adopted_children;
    conglomerate *my_conglom_root;
    sound_and_pfx_interface *my_sound_and_pfx_interface;
    int16_t field_3C;
    int16_t field_3E;
    int8_t field_40;
    int8_t field_41;
    int8_t rel_po_idx;
    int8_t proximity_map_reference_count;

    bool is_flagged(unsigned int a2) const
    {
        return (a2 & this->field_4) != 0;
    }

    auto get_id() const {
        return this->field_10;
    }
};

VALIDATE_SIZE(entity_base, 0x44u);
