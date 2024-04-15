#pragma once

#include "bit.h"
#include "float.hpp"
#include "variable.h"

struct entity;
struct mString;
struct terrain;
struct vector3d;

struct world_dynamics_system
{
    char field_0[0x1AC];
    terrain *the_terrain;
    char field_1B0[0x40 * 2];
    entity *field_230[1];
    int field_234;
    int num_players;

    auto *get_the_terrain() {
        return the_terrain;
    }

    entity *get_hero_ptr(int index);

    void remove_player(int player_num)
    {
        void (__fastcall *func)(void *, void *, int) = bit_cast<decltype(func)>(0x00558550);

        func(this, nullptr, player_num);
    }

    void malor_point(const vector3d *a2, int a3, bool a4)
    {
        void (__fastcall *func)(void *, void *, const vector3d *, int, bool) = bit_cast<decltype(func)>(0x00530460);
        func(this, nullptr, a2, a3, a4);
    }

    int add_player(const mString &a2)
    {
        int (__fastcall *func)(void *, void *, const mString *) = bit_cast<decltype(func)>(0x0055B400);

        return func(this, nullptr, &a2);
    }

    void frame_advance(Float a2);

};

inline Var<world_dynamics_system *> g_world_ptr{0x0095C770};

extern void wds_patch();

