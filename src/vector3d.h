#pragma once

struct vector3d
{
    float x, y, z;

    float operator[](int i) {
        return (&x)[i];
    }
};

const vector3d ZEROVEC{0, 0, 0};
