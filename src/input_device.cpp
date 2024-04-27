#include "input_device.h"

#include "common.h"
#include "utility.h"
#include "vtbl.h"

VALIDATE_SIZE(input_device, 0x8);

input_device::input_device()
{
    m_vtbl = CAST(m_vtbl, 0x0088E4D0);
    this->field_4 = INVALID_DEVICE_ID;
}

uint8_t input_device::normalize(int a1) {
    return a1;
}

bool input_device::is_connected() const {

    return this->m_vtbl->is_connected(this);
}

int input_device::get_axis_id(int a1) {

    return this->m_vtbl->get_axis_id(this, nullptr, a1);
}

float input_device::get_axis_delta(int a2, int a3) {

    return this->m_vtbl->get_axis_delta(this, nullptr, a2, a3);
}

void input_device::poll() {

    return this->m_vtbl->poll(this);
}

float input_device::get_axis_old_state(int a2, int a3) {

    return this->m_vtbl->get_axis_old_state(this, nullptr, a2, a3);
}

float input_device::get_axis_state(int a2, int a3) {

    return this->m_vtbl->get_axis_state(this, nullptr, a2, a3);
}

device_id_t input_device::get_id() const
{
    return this->m_vtbl->get_id(this);
}
