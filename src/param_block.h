#pragma once

#include "entity_base.h"
#include "entity_base_vhandle.h"
#include "mstring.h"
#include "string_hash.h"
#include "vector3d.h"

#include <cassert>

template<typename T>
struct variance_variable {
    T field_0;
    T field_4;

    variance_variable() {
        this->field_4 = 0;
        this->field_0 = 0;
    }
};

namespace ai {

enum param_types {
    PT_FLOAT = 0,
    PT_INTEGER = 1,
    PT_STRING_HASH = 2,
    PT_FIXED_STRING = 3,
    PT_VECTOR_3D = 4,
    PT_FLOAT_VARIANCE = 5,
    PT_ENTITY = 6,
    PT_POINTER = 7,
};


struct param_block {

    struct param_data {
        union U {
            int i;
            float f;
            string_hash hash;
            char *str;
            vector3d *vec3;
            variance_variable<float> *float_variance;
            entity_base_vhandle *ent;
        } m_union;
        param_types my_type;
        string_hash field_8;

        auto get_data_type() const {
            return this->my_type;
        }

        string_hash get_data_hash() const {
            return this->m_union.hash;
        }

        float & get_data_float() {
            assert(my_type == PT_FLOAT);
            return m_union.f;
        }

        int & get_data_int() {
            assert(my_type == PT_INTEGER);
            return m_union.i;
        }

        const char * get_data_string()
        {
            assert(my_type == PT_FIXED_STRING);

            return this->m_union.str;
        }

        vector3d * get_data_vector3d()
        {
            assert(my_type == PT_VECTOR_3D);
            return this->m_union.vec3;
        }

        auto &get_data_float_variance() {
            assert(my_type == PT_FLOAT_VARIANCE);
            return m_union.float_variance;
        }

        entity_base_vhandle * get_data_entity()
        {
            assert(my_type == PT_ENTITY);

            return this->m_union.ent;
        }

        mString get_value_in_string_form()
        {
            mString result {};
            switch ( this->my_type )
            {
            case PT_FLOAT: {
                auto data_float = this->get_data_float();
                result = mString {0, "%.1f", data_float};
                break;
            }
            case PT_INTEGER: {
                auto data_int = this->get_data_int();
                result = mString {0, "%d", data_int};
                break;
            }
            case PT_STRING_HASH: {
                auto v22 = this->get_data_hash();
                auto *v4 = v22.to_string();
                result = mString {v4};
                break;
            }
            case PT_FIXED_STRING: {
                auto *v5 = this->get_data_string();
                result = mString {v5};
                break;
            }
            case PT_VECTOR_3D: {
                auto v17 = this->get_data_vector3d()->z;
                auto v16 = this->get_data_vector3d()->y;
                auto v6 =  this->get_data_vector3d()->x;
                result = mString {0, "%.1f %.1f %.1f", v6, v16, v17};
                break;
            }
            case PT_FLOAT_VARIANCE: {
                auto v7 = *this->get_data_float_variance();
                auto v18 = v7.field_4;
                auto v9 = v7.field_0;
                result = mString {0, "%.1f %.1f", v9, v18};
                break;
            }
            case PT_ENTITY: {
                mString v14 {};
                auto *v10 = this->get_data_entity();
                if ( v10->get_volatile_ptr() != nullptr )
                {
                    auto *ent = v10->get_volatile_ptr();
                    auto id = ent->get_id();
                    auto *v27 = id.to_string();
                    v14 = mString {0, "%s", v27};
                }
                else
                {
                    v14 = mString {0, "%s", "<NULL>"};
                }

                result = v14;
                break;
            }
            case PT_POINTER: {
                result = mString {"<NULL>"};
                break;
            }
            default:
                assert(0 && "Unhandled AI::param_block::param_data::param_type type!");
                return result;
            }

            return result;
        }
    };

    struct param_data_array {
        mVector<param_block::param_data> field_0;
        int field_14;
    };

    int my_curr_mode;
    param_data_array *param_array;
    bool field_8;
};

}
