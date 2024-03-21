#pragma once

#include "signaller.h"

#include "common.h"
#include "string_hash.h"
#include "vtbl.h"
#include "variable.h"
#include "vector3d.h"

#include "list.hpp"

struct collision_geometry;
struct region;
struct po;
struct time_interface;

template<typename T, uint32_t N>
struct fixed_vector;

struct entity : signaller 
{
    static constexpr inline auto FIXED_REGIONS_ARRAY_SIZE = 2;

    region *regions[FIXED_REGIONS_ARRAY_SIZE];
    fixed_vector<region *, 7> *extended_regions;
    collision_geometry *colgeom;
    time_interface *field_58;
    int field_5C;
    int field_60;
    int field_64;

    void suspend(bool a1) {
        auto &func = get_vfunc(m_vtbl, 0x1B8);

        func(this, 0, a1);
    }

    void unsuspend(bool a1) {
        auto &func = get_vfunc(m_vtbl, 0x1BC);

        func(this, 0, a1);
    }

    region * get_primary_region()
    {
        region *(__fastcall *func)(void *) = bit_cast<decltype(func)>(0x004C0760);
        return func(this);
    }

    vector3d *get_abs_position()
    {
        vector3d * (__fastcall *func)(void *) = bit_cast<decltype(func)>(0x0048AC00);
        return func(this);
    }

    po *get_abs_po()
    {
        po * (__fastcall *func)(void *) = bit_cast<decltype(func)>(0x0048AC20);
        return func(this);
    }

    bool is_an_actor() const {
        bool (__fastcall *func)(const void *) =
            bit_cast<decltype(func)>(get_vfunc(m_vtbl, 0x64));
        return func(this);
    }

    static int find_entities(int a1)
    {
        return CDECL_CALL(0x004D67D0, a1);
    }

    static inline Var<_std::list<entity *> *> found_entities {0x0095A6E0};
};

VALIDATE_SIZE(entity, 0x68u);
VALIDATE_OFFSET(entity, my_handle, 0x1C);
