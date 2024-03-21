#pragma once

#include "mstring.h"
#include "utility.h"

#include <cstdint>
#include <windows.h>

struct os_file {
    enum mode_flags
    {
        FILE_READ = 1,
        FILE_WRITE = 2,
        FILE_MODIFY = 3,
        FILE_APPEND = 4
    };

    enum filepos_t {
        FP_BEGIN,
        FP_CURRENT,
        FP_END
    };

    mString m_path;
    uint32_t flags;
    bool opened;
    bool field_15;

    HANDLE io;

    uint32_t field_1C;
    uint32_t m_fileSize;
    bool field_24;
    uint32_t m_offset;
    uint32_t field_2C;
    uint32_t field_30;

    //0x0059EAA0
    explicit os_file(const mString &a2, int dwShareMode)
    {
        void (__fastcall *func)(void *, void *, const mString *, int) = CAST(func, 0x0059EAA0);
        func(this, nullptr, &a2, dwShareMode);
    }

    int write(const void *lpBuffer, int nNumberOfBytesToWrite)
    {
        int (__fastcall *func)(void *, void *, const void *, int) = CAST(func, 0x00598C30);
        return func(this, nullptr, lpBuffer, nNumberOfBytesToWrite);
    }

};
