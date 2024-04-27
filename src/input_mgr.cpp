#include "input_mgr.h"

#include "common.h"
#include "input.h"
#include "keyboard_device.h"
#include "trace.h"
#include "utility.h"

#include <cassert>

VALIDATE_SIZE(input_mgr, 0x5C);

bool IS_JOYSTICK_DEVICE(int id) {
    return id >= 0xF4240 && id <= 0xF4247;
}

bool IS_KEYBOARD_DEVICE(int id) {
    return id == 0x1E8480;
}

bool IS_MOUSE_DEVICE(device_id_t id) {
    return id == 0x2DC6C0;
}

void input_mgr::map_control(int a2, device_id_t a3, int axis)
{
    void (__fastcall *func)(void *, void *, int, device_id_t, int) = bit_cast<decltype(func)>(0x005D8660);
    func(this, nullptr, a2, a3, axis);
}

void input_mgr::scan_devices()
{
    TRACE("input_mgr::scan_devices");

    if constexpr (1)
    {
        if (Input::instance() == nullptr || Input::instance()->m_din == nullptr) {
            keyboard_device::instance->clear();
        } else {
            keyboard_device::instance->initialize(0);
            this->insert_device(keyboard_device::instance);
        }

    }

    if constexpr (0)
    {}
    else
    {
        void (__fastcall *func)(void *) = CAST(func, 0x00599090);
        func(this);
    }

}

void input_mgr::insert_device(input_device *a2)
{
    TRACE("input_mgr::insert_device");

    printf("0x%X\n", a2->get_id());

    if constexpr(0)
    {
        auto *v2 = a2;
        auto id = a2->get_id();

        input_device ** (__fastcall *find)(void *, void *edx, const device_id_t *) = CAST(find, 0x005E8400);
        auto found_device = find(&this->field_8, nullptr, &id);
        *found_device = v2;

        if ( !IS_JOYSTICK_DEVICE(v2->get_id()) )
        {
            if ( !IS_KEYBOARD_DEVICE(v2->get_id()) )
            {
                if ( IS_MOUSE_DEVICE(v2->get_id()) ) {
                    *((DWORD *)&this[0xFFFE027F] + v2->get_id() - 0x14) = (DWORD)v2;
                }
            }
            else
            {
                *((DWORD *)&this[0xFFFEAC55] + v2->get_id() - 0xF) = (DWORD)v2;
            }
        }
        else
        {
            *((DWORD *)&this[0xFFFF562B] + v2->get_id() - 0x11) = (DWORD)v2;
        }
    }
    else
    {
        void (__fastcall *func)(void *, void *edx, input_device *) = CAST(func, 0x005DC140);
        func(this, nullptr, a2);
    }
}

void input_mgr_patch()
{
    {
        auto address = func_address(&input_mgr::scan_devices);
        REDIRECT(0x0055D696, address);
    }

    if constexpr (0)
    {
        auto address = func_address(&input_mgr::map_control);
        REDIRECT(0x00605C41, address);
    }
}
