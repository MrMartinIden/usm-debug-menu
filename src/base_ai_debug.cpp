#include "base_ai_debug.h"

#include "actor.h"
#include "base_ai_core.h"
#include "debug_menu.h"
#include "info_node.h"
#include "os_file.h"

#include <cstdio>
#include <string>

static ai::ai_core *debug_menu_ai_core = nullptr;

static const char *TYPE_NAME_ARRAY[8] {
    "float",
    "int",
    "string_hash",
    "fixedstring",
    "vector3d",
    "float_variance",
    "entity",
    "pointer"
};


void handle_export_block(debug_menu_entry *arg0)
{
    auto *the_pb = static_cast<ai::param_block *>(arg0->get_data());
    assert(the_pb != nullptr);

    auto *v2 = debug_menu_ai_core->get_actor(0);
    auto id = v2->get_id();
    auto v4 = id.to_string();
    mString a1 {0, "param_dump_%s.txt", v4};
    os_file file {a1, 2};
    mString v32 {};

    auto *v31 = the_pb->param_array;
    if ( v31 != nullptr )
    {
        auto *v8 = id.to_string();
        v32 = mString {0, "// Parameter list for %s\r\n", v8};
        auto v14 = v32.length();
        auto *v9 = v32.c_str();
        file.write(v9, v14);

        for ( auto &v28 : v31->field_0 )
        {
            auto v21 = v28->get_value_in_string_form();
            auto v19 = v28->field_8;

            auto v15 = v21.c_str();
            auto *v13 = v19.to_string();
            auto data_type = v28->get_data_type();
            v32 = mString {0, "%s %s %s\r\n", TYPE_NAME_ARRAY[data_type], v13, v15};
            auto v16 = v32.length();
            auto *v11 = v32.c_str();
            file.write(v11, v16);
        }
    }
    else
    {
        v32 = mString {"// no parameters defined in this block.\r\n"};
        auto v17 = v32.length();
        auto *v12 = v32.c_str();
        file.write(v12, v17);
    }

    debug_menu::hide();
}

std::string ai_param_render_callback(debug_menu_entry *a2)
{
    using namespace ai;

    mString result {};

    auto *the_data = static_cast<ai::param_block::param_data *>(a2->get_data());
    assert(the_data != nullptr);

    switch ( the_data->get_data_type() )
    {
    case PT_STRING_HASH: {
        auto v19 = the_data->get_data_hash();
        auto v18 = the_data->field_8;
        auto *v15 = v19.to_string();
        auto *v2 = v18.to_string();
        result = mString {0, "%s %s (hash)", v2, v15};
        break;
    }
    case PT_FIXED_STRING: {
        auto v20 = the_data->field_8;
        auto *v16 = the_data->get_data_string();
        auto v4 = v20.to_string();
        result = mString {0, "%s %s (fixedstring)", v4, v16};
        break;
    }
    case PT_VECTOR_3D: {
        vector3d v32 = *the_data->get_data_vector3d();
        auto v21 = the_data->field_8;
        auto v13 = v32[2];
        auto v11 = v32[1];
        auto v10 = v32[0];
        auto *v6 = v21.to_string();
        result = mString {0, "%s (%.2f %.2f %.2f) (vector3d)", v6, v10, v11, v13};
        break;
    }
    case PT_FLOAT_VARIANCE: {
        auto v31 = *the_data->get_data_float_variance();
        auto v22 = the_data->field_8;
        auto v14 = v31.field_4;
        auto v12 = v31.field_0;
        auto *v8 = v22.to_string();
        result = mString {0, "%s (b%.2f v%.2f) (float variance)", v8, v12, v14};
        break;
    }
    default: {
        auto v23 = the_data->field_8;
        auto data_type = the_data->get_data_type();
        auto *v9 = v23.to_string();
        printf("Unsupported param data type for %s %d.  This code needs to be updated\n", v9, data_type);
        assert(0);
        return result.c_str();
    }
    }

    return result.c_str();
}

void populate_param_block(debug_menu_entry *a2)
{
    using namespace ai;

    auto *the_pb = static_cast<ai::param_block *>(a2->get_data());
    assert(the_pb != nullptr);

    auto name_menu = a2->get_script_handler();
    auto *v26 = create_menu(name_menu.c_str(), debug_menu::sort_mode_t::ascending);
    a2->set_submenu(v26);

    debug_menu_entry *v27 = nullptr;
    auto *v25 = the_pb->param_array;
    if ( v25 != nullptr )
    {
        for ( auto &v22 : v25->field_0 )
        {
            auto data_hash = v22->field_8;
            auto *v2 = data_hash.to_string();
            mString a1 {0, "%s", v2};

            debug_menu_entry v27 {a1};

            switch ( v22->get_data_type() )
            {
            case PT_FLOAT: {
                auto *v3 = bit_cast<float *>(v22);
                
                v27.set_pt_fval(v3);
                v27.set_step_size(0.30000001);
                v27.set_step_scale(30.0);
                v27.set_max_value(3.4028235e38);
                v27.set_min_value(-3.4028235e38);
                break;
            }
            case PT_INTEGER: {
                auto *v4 = bit_cast<int *>(v22);
                
                v27.set_p_ival(v4);
                v27.set_max_value(2147483600.0);
                v27.set_min_value(-2147483600.0);
                break;
            }
            case PT_STRING_HASH:
            case PT_FIXED_STRING:
            case PT_VECTOR_3D:
            case PT_FLOAT_VARIANCE:
                v27.set_render_cb(ai_param_render_callback);
                break;
            default:
                auto data_type = v22->get_data_type();
                printf("Unknown param data type %d.  This code needs to be updated\n", data_type);
                assert(0);
                return;
            }

            v27.set_data(v22);
            v26->add_entry(&v27);
        }

        v27 = create_menu_entry(mString {"--Export this block--"});
        v27->set_game_flags_handler(handle_export_block);
        v27->set_data(the_pb);
    }
    else
    {
        v27 = create_menu_entry(mString {"--None defined--"});
    }

    v26->add_entry(v27);
}

void ai_core_menu_handler(debug_menu_entry *a2)
{
    auto *the_core = static_cast<ai::ai_core *>(a2->get_data());
    assert(the_core != nullptr);

    debug_menu_ai_core = the_core;

    auto name_menu = a2->get_script_handler();
    auto *v21 = create_menu(name_menu.c_str(), debug_menu::sort_mode_t::ascending);
    a2->set_submenu(v21);

    debug_menu_entry v20 {mString {"-Core params"}};
    v20.set_submenu(nullptr);
    v20.set_game_flags_handler(populate_param_block);
    auto *v2 = the_core->get_param_block();
    v20.set_data(v2);
    v21->add_entry(&v20);

    auto *v19 = the_core->field_60;
    if ( v19 != nullptr )
    {
        for ( auto &v16 : (*v19) )
        {
            auto v5 = v16->field_4;
            auto *v3 = v5.to_string();

            debug_menu_entry v20 {mString {0, "%s inode params", v3}};
            v20.set_submenu(nullptr);
            v20.set_game_flags_handler(populate_param_block);
            auto &v4 = v16->m_param_block;
            v20.set_data(&v4);
            v21->add_entry(&v20);
        }
    }
}

void populate_ai_root(debug_menu_entry *arg0)
{
    auto name_menu = arg0->get_script_handler();
    debug_menu *v20 = create_menu(name_menu.c_str(), debug_menu::sort_mode_t::undefined);
    arg0->set_submenu(v20);

    static auto *g_the_ai_core_list = ai::ai_core::the_ai_core_list_high();

    if ( g_the_ai_core_list != nullptr )
    {
        for ( auto &v17 : (*g_the_ai_core_list) )
        {
            auto *v3 = v17->get_actor(0);
            if ( !v3->is_flagged(0x800u) )
            {
                auto id = v3->get_id();
                auto *v7 = id.to_string();
                debug_menu_entry v16 {mString {v7}};

                v16.set_data(v17);
                v16.set_submenu(nullptr);
                v16.set_game_flags_handler(ai_core_menu_handler);
                v20->add_entry(&v16);
            }
        }
    }
}

void create_ai_root_menu(debug_menu *parent)
{
    assert(parent != nullptr);

    debug_menu_entry v5 {mString {"AI"}};
    v5.set_submenu(nullptr);
    v5.set_game_flags_handler(populate_ai_root);
    parent->add_entry(&v5);
}
