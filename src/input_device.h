#pragma once

#include "device_id.h"
#include "float.hpp"

#include <cstdint>

struct input_device {

    struct {
        int field_0;
        int get_name;
        device_id_t (__fastcall *get_id)(const input_device *);
        int (__fastcall *get_axis_count)(const input_device *);
        int (__fastcall *get_axis_id)(input_device *, void *, int a1);
        float (__fastcall *get_axis_state)(input_device *, void *edx, int , int);
        float (__fastcall *get_axis_old_state)(input_device *, void *edx, int , int);
        float (__fastcall *get_axis_delta)(input_device *, void *edx, int , int );
        void (__fastcall *poll)(input_device *);
        int normalize;
        void (__fastcall *finalize)(input_device *, void *, bool);
        bool (__fastcall *is_connected)(const input_device *);
        int (__fastcall *clear_state)(input_device *);
        void (__fastcall *vibrate)(input_device *, void *edx, int , int , int , int a4);
        void (__fastcall *vibrate_0)(input_device *, void *edx, Float );
        void (__fastcall *stop_vibration)(input_device *);
        bool (__fastcall *is_vibrator_present)(const input_device *);

    } * m_vtbl;

    int field_4;

    input_device();

    //0x005B0A60
    //virtual
    uint8_t normalize(int a1);

    //virtual
    bool is_connected() const;

    //virtual
    int get_axis_id(int a1);

    //virtual
    float get_axis_delta(int a2, int a3);

    //virtual
    void poll();

    //virtual
    float get_axis_old_state(int a2, int a3);

    //virtual
    float get_axis_state(int a2, int a3);

    //virtual
    device_id_t get_id() const;
};
