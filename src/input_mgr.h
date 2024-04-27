#pragma once

#include "device_id.h"
#include "variable.h"

struct input_device;

struct input_mgr
{
    int field_0;
    struct {

        void disable_vibration()
        {
            void (__fastcall *func)(void *) = (decltype(func)) 0x005C5440;
            func(this);
        }

        void enable_vibration()
        {
            void (__fastcall *func)(void *) = (decltype(func)) 0x005C5430;
            func(this);
        }

    } *rumble_ptr;
    int field_8[10];
    void *field_30[1];
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    void *keyboard_devices[1];
    void *mouse_devices[1];
    device_id_t field_58;

    void map_control(int a2, device_id_t a3, int axis);

    void scan_devices();

    void insert_device(input_device *a2);

    static inline Var<input_mgr *> instance {0x009685DC};
};

extern void input_mgr_patch();
