#pragma once

#include "variable.h"

#include <cstdint>
#include <windows.h>

#include <dinput.h>

struct IDirectInput8A;
struct InputSettings;
struct IDirectInputDevice8A;

struct Input {
    bool field_0;
    char empty0[3];
    int field_4;
    bool field_8;
    bool field_9;
    char empty1[2];
    IDirectInputDevice8A *m_di_keyboard;
    IDirectInputDevice8A *m_di_mouse;
    int field_14[10];
    int field_3C[10];
    int field_64[10];
    int field_8C[20];
    int empty2[250];
    DIMOUSESTATE2 m_mouse_state;
    DIMOUSESTATE2 m_old_mouse_state;
    char field_4EC[4];
    int field_4F0;
    int field_4F4;

    DIJOYSTATE2 field_4F8[10];
    DIJOYSTATE2 field_F98[10];
    DIMOUSESTATE2 field_1A38;
    int field_1A4C[680];
    char field_24EC[256];
    char m_state_keys[256];
    char m_old_state_keys[256];
    IDirectInput8A *m_din;
    int field_27F0[10][4];
    bool m_initialized;
    char empty6[3];
    HWND m_hwnd;
    float m_sensitivity;
    int empty26[2];
    char m_keys[222][256];
    int field_106A4;

    int empty27[2175];
    char m_mouseLeft[30];
    char m_mouseMiddle[30];
    char m_mouseRight[30];
    char m_mouseBtn[30];
    char m_mouseAxis[30];
    char m_mouseWheelUp[30];
    char m_mouseWheelDown[30];

    char m_gamepadAxis[30];
    char m_gamepadBtn[30];
    char m_gamepadPoV[30];
    uint32_t field_129D0;
    uint32_t m_current_connected;
    InputSettings *field_129D8[4];

    static inline Var<Input *> instance {0x00987948};
};

extern void Input_patch();
