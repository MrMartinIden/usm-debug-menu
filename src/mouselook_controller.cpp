#include "mouselook_controller.h"

#include "game.h"
#include "trace.h"
#include "utility.h"
#include "variable.h"

void mouselook_controller::_frame_advance(Float a2)
{
    TRACE("mouselook_controller::frame_advance");

    //dirty hack
    {
        static Var<actor *> g_debug_cam_target_actor {0x0095C758};
        g_debug_cam_target_actor() = bit_cast<actor *>(g_world_ptr()->get_hero_ptr(0));
    }

    void (__fastcall *func)(void *, void *, Float) = CAST(func, 0x00528BB0);
    func(this, nullptr, a2);
}

void mouselook_controller_patch()
{
    {
        auto address = func_address(&mouselook_controller::_frame_advance);
        set_vfunc(0x00889118, address);
    }
}
