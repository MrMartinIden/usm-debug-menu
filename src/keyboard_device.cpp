#include "keyboard_device.h"

#include "game.h"
#include "input.h"
#include "keyboard.h"
#include "trace.h"
#include "utility.h"

#include <optional>

keyboard_device::keyboard_device()
{
    using vtbl_t = std::decay_t<decltype(*m_vtbl)>;
    Var<vtbl_t> tmp {0x0088EA80};
    static vtbl_t vtbl = tmp();

    this->m_vtbl = &vtbl;
    this->field_4 = INVALID_DEVICE_ID;

    {
        auto address = func_address(&keyboard_device::_clear_state);
        this->m_vtbl->clear_state = CAST(this->m_vtbl->clear_state, address);
    }

    {
        auto address = func_address(&keyboard_device::_get_axis_state);
        this->m_vtbl->get_axis_state = CAST(this->m_vtbl->get_axis_state, address);
    }

    {
        auto address = func_address(&keyboard_device::_get_axis_old_state);
        this->m_vtbl->get_axis_old_state = CAST(this->m_vtbl->get_axis_old_state, address);
    }

    {
        auto address = func_address(&keyboard_device::_get_axis_delta);
        this->m_vtbl->get_axis_delta = CAST(this->m_vtbl->get_axis_delta, address);
    }

    {
        auto address = func_address(&keyboard_device::_poll);
        this->m_vtbl->poll = CAST(this->m_vtbl->poll, address);
    }

    {
        auto address = func_address(&keyboard_device::_is_connected);
        this->m_vtbl->is_connected = CAST(this->m_vtbl->is_connected, address);
    }

}

static keyboard_device g_device {};

keyboard_device * keyboard_device::instance = &g_device;

mString keyboard_device::get_name() const
{
    mString a1 {"USB Keyboard"};
    return a1;
}

void keyboard_device::clear()
{
    this->field_4 = INVALID_DEVICE_ID;
}

void keyboard_device::initialize(int a2)
{
    this->field_4 = 0x1E8480;
    this->field_8 = a2;
}

void keyboard_device::_clear_state()
{
    ;
}

float keyboard_device::_get_axis_state(int axis, int a3)
{
    TRACE("keyboard_device::get_axis_state");

    printf("axis = %d, %d\n", axis, a3);

    if (Input::instance() != nullptr)
    {
        static uint16_t key_codes[KB_NUM_AXES] {};

#define register_key_code(key)  key_codes[KB_##key] = DIK_##key

        register_key_code(I);
        register_key_code(K);
        register_key_code(T);
        register_key_code(J);
        register_key_code(L);
        register_key_code(O);
        register_key_code(U);
        register_key_code(RSHIFT);
        register_key_code(RALT);

#undef register_key_code

        float result = (Input::instance()->m_state_keys[key_codes[axis]] != 0);
        return result;
    }

    return 0.0f;
}

float keyboard_device::_get_axis_old_state(int axis, int )
{
    return 0.0f;
}

float keyboard_device::_get_axis_delta(int axis, int a2)
{
    return this->_get_axis_state(axis, a2) - 0.0f;
}

void keyboard_device::_poll()
{
    TRACE("keyboard_device::poll");
    ;
}

bool keyboard_device::_is_connected() const {
    return this->field_4 != INVALID_DEVICE_ID;
}

bool keyboard_device::_is_vibrator_present() const {
    return false;
}
