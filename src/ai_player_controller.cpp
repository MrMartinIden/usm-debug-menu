#include "ai_player_controller.h"

#include "common.h"
#include "utility.h"
#include "variable.h"

VALIDATE_SIZE(ai_player_controller, 0x424u);

static Var<void *> g_spiderman_camera_ptr {0x00959A70};

void ai_player_controller::lock_controls(bool a2)
{
    this->field_3DC = false;

    void (__fastcall *func)(void *, void *, bool) = CAST(func, 0x004B3260);
    func(g_spiderman_camera_ptr(), nullptr, a2);
}
