#include "wds.h"

#include "common.h"
#include "game.h"
#include "message_board.h"
#include "utility.h"

#include <cassert>

VALIDATE_OFFSET(world_dynamics_system, field_230, 0x230);


entity *world_dynamics_system::get_hero_ptr(int index)
{
    constexpr auto MAX_GAME_PLAYERS = 1;

    assert(index >= 0 && index <= MAX_GAME_PLAYERS);

    auto *result = this->field_230[index];
    return result;
}

void world_dynamics_system::frame_advance(Float a2)
{
    void (__fastcall *func)(void *, void *, Float) = CAST(func, 0x00558370);
    func(this, nullptr, a2);

    {
        g_game_ptr()->mb->frame_advance(a2);
    }
}

void wds_patch()
{
    {
        auto address = func_address(&world_dynamics_system::frame_advance);
        REDIRECT(0x0055A0F7, address);
    }
}
