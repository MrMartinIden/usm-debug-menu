#include "game.h"

#include "common.h"
#include "debug_menu.h"
#include "message_board.h"

VALIDATE_OFFSET(game, gamefile, 0xC0);
VALIDATE_OFFSET(game, field_172, 0x172);
VALIDATE_OFFSET(game, field_280, 0x280);

mString sub_55DD80(const vector3d &a2)
{
    mString a1 {0, "<%.3f,%.3f,%.3f>", a2.x, a2.y, a2.z};
    return a1;
}

mString game::get_camera_info()
{
    auto *v2 = this->field_5C;

    mString v22;
    if ( v2->get_primary_region() != nullptr )
    {
        auto *v4 = v2->get_primary_region();
        auto &v5 = v4->get_name();
        auto *v6 = v5.to_string();
        v22 = mString{v6};
    }
    else
    {
        v22 = mString{"none"};
    }

    mString v33 = v22;


    auto &v18 = *v2->get_abs_position();
    auto *v8 = g_world_ptr()->the_terrain;
    auto *v32 = v8->find_region(v18, nullptr);
    if ( v32 != nullptr )
    {
        auto &v9 = v32->get_name();
        auto *v10 = v9.to_string();
        v33 = {v10};
    }

    auto &v12 = *v2->get_abs_position();
    auto v31 = sub_55DD80(v12);

    auto &v14 = *v2->get_abs_po();
    auto &v15 = v14.get_z_facing();

    auto v30 = sub_55DD80(v15);
    auto *v20 = v30.c_str();
    auto *v19 = v31.c_str();
    auto *v16 = v33.c_str();

    mString v29 {0, "CAMERA @ %s %s, f = %s", v16, v19, v20};

    auto v24 = " " + v33;

    v29 += v24;
    
    return v29;
}

mString game::get_analyzer_info()
{
    auto v16 = string_hash("SCENE_ANALYZER_CAM");
    auto *v3 = entity_handle_manager::find_entity(v16, entity_flavor_t::CAMERA, false);

    auto &v14 = *v3->get_abs_position();
    auto *v4 = g_world_ptr()->the_terrain;
    auto *v26 = v4->find_region(v14, nullptr);

    mString v25 {""};
    if ( v26 != nullptr )
    {
        auto &v5 = v26->get_name();
        auto *v6 = v5.to_string();
        v25 = v6;
    }

    auto &v8 = *v3->get_abs_position();
    auto v24 = sub_55DD80(v8);

    auto &v10 = *v3->get_abs_po();
    auto &v11 = v10.get_z_facing();
    auto v23 = sub_55DD80(v11);

    auto *v15 = v23.c_str();
    auto *v12 = v24.c_str();

    mString a1 {0, "ANALYZER @ %s, f = %s", v12, v15};
    auto v17 = " " + v25;
    a1 += v17;
    return a1;
}

mString game::get_hero_info()
{
    auto *hero_ptr = g_world_ptr()->get_hero_ptr(0);
    if ( hero_ptr == nullptr )
    {
        mString result {"(hero does not exist!)"};
        return result;
    }

    region *v29 = nullptr;
    if ( hero_ptr != nullptr )
    {
        v29 = hero_ptr->get_primary_region();
    }

    mString v28 {"none"};
    if ( v29 != nullptr )
    {
        auto &v4 = v29->get_name();
        auto *v5 = v4.to_string();
        v28 = {v5};
    }

    auto v27 = [&]() -> mString
    {
        if ( hero_ptr != nullptr )
        {
            auto &v6 = *hero_ptr->get_abs_position();
            return sub_55DD80(v6);
        }

        return mString{"N/A"};
    }();

    vector3d v15;
    if ( hero_ptr != nullptr )
    {
        auto *v7 = bit_cast<actor *>(hero_ptr)->physical_ifc();
        v15 = v7->get_velocity();
    }
    else
    {
        v15 = ZEROVEC;
    }

    mString v25{0, "HERO @ %s ", v28.c_str()};

    auto *v9 = v27.c_str();
    v25.append(v9, -1);
    v25.append(", v = ", -1);

    auto v14 = sub_55DD80(v15);
    v25.append(v14.c_str(), -1);

    return v25;
}

void game::show_debug_info()
{
    auto DEBUG_INFO_FONT_PCT = os_developer_options::instance()->get_int(mString{"DEBUG_INFO_FONT_PCT"});
    auto v15 = (float)DEBUG_INFO_FONT_PCT / 100.0;
    auto a1 = this->get_hero_info();

    vector2di v13 {50, 40};
    auto *v4 = a1.c_str();
    nglListAddString(nglSysFont(), (float)v13.x, (float)v13.y, 1.0, v15, v15, v4);

    auto v12 = this->get_camera_info();
    v13.y += 20;
    auto *v5 = v12.c_str();
    nglListAddString(nglSysFont(), (float)v13.x, (float)v13.y, 1.0, v15, v15, v5);

    auto v11 = this->get_analyzer_info();
    v13.y += 20;
    auto *v6 = v11.c_str();
    nglListAddString(nglSysFont(), (float)v13.x, (float)v13.y, 1.0, v15, v15, v6);
}

void game::frame_advance_level(Float time_inc)
{
    printf("game::frame_advance_level\n");

    {
        static int dword_14EEAC4 {-1};
        mem_check_leaks_since_checkpoint(dword_14EEAC4, 1);
        dword_14EEAC4 = mem_set_checkpoint();
        mem_print_stats("\nMemory log\n");
    }

    void (__fastcall *func)(void *, void *edx, Float) = (decltype(func)) 0x0055D650;
    func(this, nullptr, time_inc);
}

void game::set_camera(int camera_state)
{
    printf("camera_state = %d\n", camera_state);

    void (__fastcall *func)(void *, void *edx, int) = CAST(func, 0x0054F8C0);
    func(this, nullptr, camera_state);

    {
        if ( 1 == camera_state )
        {
            if ( g_debug_camera_entry != nullptr ) {
                g_debug_camera_entry->set_ival(true, true);
            }
        }
        else if ( 2 != camera_state )
        { 
            if ( g_debug_camera_entry != nullptr ) {
                g_debug_camera_entry->set_ival(false, true);
            }
        }
    }
}

void game::message_board_init()
{
    this->mb = new message_board {};
}

void game_patch()
{
    auto address = func_address(&game::frame_advance_level);
    REDIRECT(0x0055D8C2, address);

    {
        auto address = func_address(&game::set_camera);
        REDIRECT(0x00552FA3, address);
        REDIRECT(0x00552FC2, address);
    }

    {
        auto address = func_address(&game::message_board_init);
        REDIRECT(0x00552E7C, address);
    }
}
