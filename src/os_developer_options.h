#pragma once

#include "common.h"
#include "func_wrapper.h"
#include "mstring.h"
#include "variable.h"

#include <algorithm>
#include <iterator>
#include <optional>

#include <windows.h>

inline Var<int[76]> int_defaults{0x00936A70};

inline Var<const char *[76]> int_names { 0x00936940 };

inline Var<BOOL[150]> flag_defaults{0x00936678};

inline Var<const char *[150]> flag_names { 0x00936420 };

struct os_developer_options
{
    enum strings_t {
        SOUND_LIST = 0,
        SCENE_NAME = 1,
        HERO_NAME = 2,
        GAME_TITLE = 3,
        GAME_LONG_TITLE = 4,
        SAVE_GAME_DESC = 5,
        VIDEO_MODE = 6,
        GFX_DEVICE = 7,
        FORCE_DEBUG_MISSION = 8,
        FORCE_LANGUAGE = 9,
        SKU = 10,
        CONSOLE_EXEC = 11,
        HERO_START_DISTRICT = 12,
        DEBUG_ENTITY_NAME = 13,
    };

    int m_vtbl;
    bool m_flags[150];
    mString m_strings[14];
    int m_ints[76];
    mString field_2AC;

    std::optional<mString> get_string(strings_t a2)
    {
        if (a2 < strings_t::SOUND_LIST || a2 > strings_t::DEBUG_ENTITY_NAME) {
            return {};
        } else {
            auto a3 = this->m_strings[a2];
            return a3;
        }
    }

    int get_int(const mString &a2)
    {
        return this->m_ints[this->get_int_from_name(a2)];
    }

    void set_int(const mString &a2, int a3)
    {
        this->m_ints[this->get_int_from_name(a2)] = a3;
    }

    void set_flag(const mString &a2, bool a3)
    {
        this->m_flags[this->get_flag_from_name(a2)] = a3;
    }

    int get_int_from_name(const mString &a1) {

        auto func = [&a1](auto &v2) {
            return (_strcmpi(v2, a1.c_str()) == 0);
        };

        auto it = std::find_if(std::begin(int_names()),
                                std::end(int_names()),
                                func);

        if (it == std::end(int_names())) {
            printf("Nonexistent int %s", a1.c_str());
        }

        return std::distance(std::begin(int_names()), it);
    }

    int get_flag_from_name(const mString &a1) const
    {
        auto func = [&a1](const char *v2) {
            return (_strcmpi(v2, a1.c_str()) == 0);
        };

        auto it = std::find_if(std::begin(flag_names()), std::end(flag_names()), func);

        size_t v3 = std::distance(std::begin(flag_names()), it);
        if (v3 == std::size(flag_names())) {
            mString out = "Nonexistent option flag " + a1;
            printf("%s\n", out.c_str());
        }

        return v3;
    }

    bool get_flag(int a2)
    {
        return this->m_flags[a2];
    }

    bool get_flag(const mString &a2) const
    {
        if constexpr (1)
        {
            return this->m_flags[this->get_flag_from_name(a2)];
        }
        else
        {
            bool (__fastcall *func)(const void *, void *, const mString *)
                = bit_cast<decltype(func)>(0x005C2F20);
            return func(this, nullptr, &a2);
        }
    }

    static inline Var<os_developer_options *> instance{0x0096858C};
};

VALIDATE_SIZE(os_developer_options, 0x2BCu);

