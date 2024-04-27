#pragma once

#include "vector3d.h"

struct ai_player_controller
{
    char field_0[0x3DC];
    bool field_3DC;
    vector3d field_3E0;
    vector3d field_3EC;
    float field_3F8;
    float field_3FC;
    vector3d field_400;
    float field_40C;
    int field_410;
    int field_414;
    int field_418;
    int field_41C;
    int field_420;

    void lock_controls(bool a2);
};
