#pragma once

#include <cstdint>

struct tlFileBuf {
    char *Buf;
    uint32_t Size;
    uint32_t UserData;
};

