#pragma once

#include "fetext.h"
#include "variable.h"
#include "common.h"
#include "os_developer_options.h"
#include "entity_handle_manager.h"
#include "vector2di.h"
#include "memory.h"
#include "ngl.h"
#include "entity.h"
#include "physical_interface.h"
#include "po.h"
#include "region.h"
#include "terrain.h"
#include "utility.h"
#include "wds.h"

struct game_process
{
    const char *field_0;
    int *field_4;
    int index;
    int num_states;
    int field_10;
    bool field_14;
};

inline Var<game_process> lores_game_process{0x00922074};

struct game_settings;
struct message_board;

struct game
{
    char field_0[0x5C];
    entity *field_5C;
    entity *current_game_camera;
    void *field_64;
    message_board *mb;
    struct {
        int field_0;
        game_process *m_first;
        game_process *m_last;
        game_process *m_end;

        auto &back()
        {
            return *(m_last - 1);
        }
    } process_stack;

    int field_7C[17];
    game_settings *gamefile;
    int field_C4[41];

    struct {
        bool level_is_loaded;
        bool single_step;
        bool physics_enabled;
        bool field_3;
        bool game_paused;
    } flag;
    bool field_16D;
    bool field_16E;
    bool field_16F;
    bool field_170;
    bool field_171;
    bool field_172;
    bool field_173;
    vector3d field_174;
    vector3d field_180[10];
    vector3d field_1F8[10];
    int field_270;
    int field_274;
    int field_278;
    int field_27C;
    int field_280;

    game_settings *get_game_settings() {
        assert(gamefile != nullptr);

        return this->gamefile;
    }

    void enable_user_camera(bool a2) {
        this->field_172 = a2;
    }

    bool is_user_camera_enabled() const {
        return this->field_172;
    }

    void set_camera(int camera_state);

    void enable_physics(bool a2)
    {
        void (__fastcall *func)(void*, int, bool) = (decltype(func)) 0x00515230;
        func(this, 0, a2);
    }

    void message_board_init();

    void enable_marky_cam(bool a2, bool a3, Float a4, Float a5)
    {
        void (__fastcall *func)(void *, void *, bool, bool, Float, Float) = bit_cast<decltype(func)>(0x005241E0);

        func(this, nullptr, a2, a3, a4, a5);
    }

    void push_process(game_process &process) {
        void (__fastcall *sub_570FD0)(void *, int, void *) = (decltype(sub_570FD0)) 0x00570FD0;

        sub_570FD0(&this->process_stack, 0, &process);

        auto &last_proc = this->process_stack.back();
        last_proc.index = 0;
        last_proc.field_10 = 0;
    }

    void push_lores()
    {
        this->push_process(lores_game_process());
    }

    void load_new_level(const mString &a1, int a2)
    {
        void (__fastcall *func)(void *, void *, const mString *, int) = bit_cast<decltype(func)>(0x00514C70);

        func(this, nullptr, &a1, a2);
    }

    void begin_hires_screenshot(int a2, int a3)
    {
        void (__fastcall *func)(void *, void *, int, int) = (decltype(func)) 0x00548C10;
        func(this, nullptr, a2, a3);
    }

    mString get_hero_info();

    mString get_camera_info();

    mString get_analyzer_info();

    void show_debug_info();

    void frame_advance_level(Float time_inc);
};

inline Var<game *> g_game_ptr{0x009682E0};

extern void game_patch();

