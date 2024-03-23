#pragma once

#include "bit.h"
#include "common.h"
#include "string_hash.h"

struct vm_executable;

struct so_data_block {
    char field_0[0xC];
};

VALIDATE_SIZE(so_data_block, 0xC);

struct script_executable;

struct script_object {
    string_hash name;
    script_executable *parent;
    script_instance *global_instance;
    void *debug_info;
    so_data_block static_data;
    int data_blocksize;
    vm_executable **funcs;
    int total_funcs;
    int field_28;
    void *instances;
    int flags;

    int find_func(string_hash a2)
    {
        int (__fastcall *func)(void *, void *, string_hash) = CAST(func, 0x0058EF80);
        return func(this, nullptr, a2); 
    }

    vm_executable * get_func(int i)
    {
        assert(funcs);
        assert(i >= 0);
        assert(i < total_funcs);
        return this->funcs[i];
    }
};

VALIDATE_SIZE(script_object, 0x34);
