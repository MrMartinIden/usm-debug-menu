#include "actor.h"

#include <cstdio>
#include <vector>

struct nalAnyPose;
struct nalBaseSkeleton;

template<typename T>
struct nalAnimClass;

struct ai_player_controller;
struct damage_interface;
struct physical_interface;

VALIDATE_OFFSET(actor, m_player_controller, 0x8C);
VALIDATE_OFFSET(actor, field_BC, 0xBC);

std::vector<nalAnimClass<nalAnyPose> *> actor::get_animations(actor *a1)
{
    std::vector<nalAnimClass<nalAnyPose> *> a2;
    a2.reserve(100u);

    auto *v11 = a1->field_BC;
    if ( v11 != nullptr )
    {
        auto &res_dir = v11->get_resource_directory();
        auto tlresource_count = res_dir.get_tlresource_count(TLRESOURCE_TYPE_ANIM_FILE);
        for (auto idx = 0; idx < tlresource_count; ++idx)
        {
            auto *tlres_loc = res_dir.get_tlresource_location(idx, TLRESOURCE_TYPE_ANIM_FILE);
            auto *animFile = (nalAnimFile *) tlres_loc->field_8;
            if ( animFile->field_0 == 0x10101 )
            {
                for ( auto *anim = bit_cast<nalAnimClass<nalAnyPose> *>(animFile->field_34);
                        anim != nullptr;
                        anim = anim->field_4 ) {
                    a2.push_back(anim);
                }
            }
        }
    }

    return a2;
}

animation_controller::anim_ctrl_handle actor::play_anim(const string_hash &a3)
{
    printf("actor::play_anim\n");
    if ( this->anim_ctrl == nullptr ) {
        this->allocate_anim_controller(0u, nullptr);
    }

    assert(anim_ctrl != nullptr);
    this->anim_ctrl->play_base_layer_anim(a3, 0.0, 32u, true);

    animation_controller::anim_ctrl_handle result{};
    result.field_0 = true;
    result.field_8 = bit_cast<decltype(result.field_8)>(this->anim_ctrl);
    return result;
}
