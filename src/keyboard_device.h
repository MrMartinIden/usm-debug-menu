#pragma once

#include "input_device.h"
#include "mstring.h"

struct keyboard_device : input_device {

    int field_8;

    keyboard_device();

    //virtual
    mString get_name() const;

    void clear();

    void initialize(int a2);

    //virtual
    void _clear_state();

    //virtual
    float _get_axis_state(int axis, int );

    float _get_axis_old_state(int a2, int a3);

    float _get_axis_delta(int axis, int a3);

    void _poll();

    bool _is_connected() const;

    bool _is_vibrator_present() const;

    static keyboard_device *instance;
};
