#pragma once

#include "utility.h"
#include "vector4d.h"

#include <cstdint>

namespace math {

template<bool>
struct Rep_Std {};

template<int Int0,
         int Int1,
         typename T0 = void,
         typename T1 = void,
         typename T2 = Rep_Std<false>>
struct VecClass {
    float field_0[4];

    auto &operator[](uint32_t idx)
    {
        return this->field_0[idx];
    }

    auto &operator[](uint32_t idx) const
    {
        return this->field_0[idx];
    }

    void sub_413530(const VecClass<Int0, Int1, T0, T1, T2> &a2, const float &a3)
    {
        auto v3 = a3;
        this->field_0[0] += v3 * a2[0];
        this->field_0[1] += v3 * a2[1];
        this->field_0[2] += v3 * a2[2];
        this->field_0[3] += v3 * a2[3];
    }

    void sub_411A50(const math::VecClass<3, 0> &a2, const math::VecClass<3, 0> &a3)
    {
        this->field_0[0] += a3[1] * a2[0];
        this->field_0[1] += a2[1] * a3[1];
        this->field_0[2] += a2[2] * a3[1];
        this->field_0[3] += a2[3] * a3[1];
    }

};

template<uint32_t, uint32_t>
struct MatClass {
    vector4d arr[4];

    vector4d GetX() const {
        return this->arr[0];
    }

    vector4d GetY() const {
        return this->arr[1];
    }

    vector4d GetZ() const {
        return this->arr[2];
    }

    void sub_4134B0(
            VecClass<3, 0> &a2,
            VecClass<3, 0> &a3,
            VecClass<3, 0> &a4,
            VecClass<3, 0> &a5) const
    {
        a2 = CAST(a2, this->arr[0]);
        a3 = CAST(a3, this->arr[1]);
        a4 = CAST(a4, this->arr[2]);
        a5 = CAST(a5, this->arr[3]);
    }
};

}
