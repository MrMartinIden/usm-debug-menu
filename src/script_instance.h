#pragma once

#include "common.h"
#include "string_hash.h"
#include "utility.h"

struct script_object;

struct vm_executable;
struct vm_thread;

struct script_instance {
	uint8_t unk[0x2C];
	script_object *m_parent;

    auto * get_parent() {
        return m_parent;
    }

    vm_thread * add_thread(const vm_executable *a2)
    {
        vm_thread * (__fastcall *func)(void *, void *, const vm_executable *) = CAST(func, 0x005AAC20);
        return func(this, nullptr, a2);
    }

    void add_thread(const vm_executable *a2, const char *a3)
    {
        void (__fastcall *func)(void *, void *, const vm_executable *, const char *) = CAST(func, 0x005AAD00);
        func(this, nullptr, a2, a3);
    }
};

