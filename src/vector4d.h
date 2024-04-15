#pragma once

struct vector4d {
    float x, y, z, w;

    auto &operator[](uint32_t idx) {
        return (&x)[idx];
    }

    auto &operator[](uint32_t idx) const {
        return (&x)[idx];
    }

    float length2() const {
        return ((x * x) + (y * y) +
                (z * z) + (w * w));
    }

};

inline float AbsSquared(const vector4d &a1) {
    return a1.length2();
}
