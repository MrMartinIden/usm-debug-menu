#include "debug_menu.h"

#include "mstring.h"

#include <algorithm>
#include <cassert>
#include <string>

#include <windows.h>

const char *to_string(debug_menu_entry_type entry_type)
{
    const char *strings[] = {
        "UNDEFINED",
        "FLOAT_E",
        "POINTER_FLOAT",
        "INTEGER",
        "POINTER_INT",
        "BOOLEAN_E",
        "POINTER_BOOL",
        "POINTER_MENU"
    };

    return strings[entry_type];
}

struct debug_menu_entry;

void entry_frame_advance_callback_default(debug_menu_entry *a1) {}

struct debug_menu;

std::string entry_render_callback_default(debug_menu_entry* entry);

std::string entry_render_callback_default(debug_menu_entry* entry)
{
    switch(entry->entry_type)
    {
    case FLOAT_E:
    case POINTER_FLOAT:
    {
		auto val = entry->get_fval();

        char str[64]{}; 
		snprintf(str, 64, "%.2f", val);
		return {str};
	}
    case BOOLEAN_E:
    case POINTER_BOOL:
    {
		bool val = entry->get_bval();

		auto *str = (val ? "True" : "False");
		return {str};
	}
    case INTEGER:
    case POINTER_INT:
    {
		auto val = entry->get_ival();

        char str[100]{}; 
		sprintf(str, "%d", val);
        return {str};
    }
    default:
        break;
    }

    return std::string{""};
}

typedef void (*menu_handler_function)(debug_menu_entry*, custom_key_type key_type);

void close_debug();

debug_menu* current_menu = nullptr;

debug_menu *debug_menu_entry::remove_menu()
{
    if ( this->m_game_flags_handler != nullptr )
    {
        if ( this->data != nullptr )
        {
            static_cast<debug_menu *>(this->data)->~debug_menu();
        }

        this->data = nullptr;
        this->m_game_flags_handler(this);
    }

    return (debug_menu *) this->data;
}

void debug_menu_entry::on_select(float a2)
{
    printf("debug_menu_entry::on_select: text = %s, entry_type = %s\n", this->text, to_string(this->entry_type));

    switch ( this->entry_type )
    {
    case UNDEFINED:
        if ( this->m_game_flags_handler != nullptr )
        {
            this->m_game_flags_handler(this);
        }

        break;
    case BOOLEAN_E:
    case POINTER_BOOL:
        this->on_change(a2, false);
        break;
    case POINTER_MENU:
        this->remove_menu();
        if ( this->data != nullptr )
        {
            current_menu = static_cast<debug_menu *>(this->data);
        }

        break;
    default:
        return;
    }
}

void debug_menu_entry::set_submenu(debug_menu *submenu)
{
    this->entry_type = POINTER_MENU;
    this->data = submenu;

    if (submenu != nullptr) {
        submenu->m_parent = current_menu;
    }
}

debug_menu_entry::debug_menu_entry(debug_menu *submenu) : entry_type(POINTER_MENU), data(submenu)
{
    strncpy(this->text, submenu->title, MAX_CHARS_SAFE);
}

void* add_debug_menu_entry(debug_menu* menu, debug_menu_entry* entry)
{
    if (entry->entry_type == POINTER_MENU)
    {
        auto *submenu = static_cast<debug_menu *>(entry->data);
        if (submenu != nullptr) {
            submenu->m_parent = menu;
        }
    }

	if (menu->used_slots < menu->capacity) {
		void* ret = &menu->entries[menu->used_slots];
		memcpy(ret, entry, sizeof(debug_menu_entry));
		++menu->used_slots;

        if (entry->entry_type == POINTER_MENU && menu->used_slots > 1) {
            std::swap(menu->entries[0], menu->entries[menu->used_slots - 1]);
        }

        if (menu->m_sort_mode != debug_menu::sort_mode_t::undefined ) {

            auto begin = menu->entries;
            auto end = begin + menu->used_slots;
            auto find_it = std::find_if(begin, end, [](debug_menu_entry &entry) {
                return entry.entry_type != POINTER_MENU;
            });

            if (find_it != end) {
                auto sort = [mode = menu->m_sort_mode](debug_menu_entry &e0, debug_menu_entry &e1) {
                    auto v7 = e0.get_script_handler();
                    auto v2 = e1.get_script_handler();
                    if (mode == debug_menu::sort_mode_t::ascending) {
                        return v7 < v2;
                    } else { //descending
                        return v7 > v2;
                    }
                };

                std::sort(begin, find_it, sort);

                std::sort(find_it, end, sort);
            }
        }

		return ret;
	}
	else {
		DWORD current_entries_size = sizeof(debug_menu_entry) * menu->capacity;
		DWORD new_entries_size = sizeof(debug_menu_entry) * EXTEND_NEW_ENTRIES;

		void* new_ptr = realloc(menu->entries, current_entries_size + new_entries_size);

		if (new_ptr == nullptr) {
			printf("RIP\n");
			__debugbreak();
		} else {
			menu->capacity += EXTEND_NEW_ENTRIES;
			menu->entries = static_cast<decltype(menu->entries)>(new_ptr);
			memset(&menu->entries[menu->used_slots], 0, new_entries_size);

			return add_debug_menu_entry(menu, entry);
		}
	}
	
	return nullptr;
}

void debug_menu::add_entry(debug_menu_entry *entry)
{
    add_debug_menu_entry(this, entry);
}

debug_menu * create_menu(const char* title, menu_handler_function function, DWORD capacity)
{
    auto *mem = malloc(sizeof(debug_menu));
    debug_menu *menu = new (mem) debug_menu {};

	strncpy(menu->title, title, MAX_CHARS_SAFE);

	menu->capacity = capacity;
	menu->handler = function;
	DWORD total_entries_size = sizeof(debug_menu_entry) * capacity;
	menu->entries = static_cast<decltype(menu->entries)>(malloc(total_entries_size));
	memset(menu->entries, 0, total_entries_size);

	return menu;
}

debug_menu * create_menu(const char* title, debug_menu::sort_mode_t mode)
{
    const auto capacity = 100u;
    auto *mem = malloc(sizeof(debug_menu));
    debug_menu* menu = new (mem) debug_menu {};

	strncpy(menu->title, title, MAX_CHARS_SAFE);

	menu->capacity = capacity;
	DWORD total_entries_size = sizeof(debug_menu_entry) * capacity;
	menu->entries = static_cast<decltype(menu->entries)>(malloc(total_entries_size));
	memset(menu->entries, 0, total_entries_size);

    menu->m_sort_mode = mode;

	return menu;
}

debug_menu_entry *create_menu_entry(const mString &str)
{
    auto *entry = new debug_menu_entry {str};
    return entry;
}

debug_menu_entry *create_menu_entry(debug_menu *menu)
{
    auto *entry = new debug_menu_entry{menu};
    return entry;
}

const char *to_string(custom_key_type key_type)
{
    if (key_type == ENTER)
    {
        return "ENTER";
    }
    else if (key_type == LEFT)
    {
        return "LEFT";
    }
    else if (key_type == RIGHT)
    {
        return "RIGHT";
    }

    return "";
}

void handle_game_entry(debug_menu_entry *entry, custom_key_type key_type)
{
    printf("handle_game_entry = %s, %s, entry_type = %s\n", entry->text, to_string(key_type), to_string(entry->entry_type));

    if (key_type == ENTER)
    {
        switch(entry->entry_type)
        {
        case UNDEFINED:
        {    
            if ( entry->m_game_flags_handler != nullptr )
            {
                entry->m_game_flags_handler(entry);
            }
            break;
        }
        case BOOLEAN_E: 
        case POINTER_BOOL:
        {
            auto v3 = entry->get_bval();
            entry->set_bval(!v3, true);
            break;
        } 
        case POINTER_MENU:
        {
            if (entry->data != nullptr)
            {
                current_menu = static_cast<decltype(current_menu)>(entry->data);
            }
            return;
        }
        default:
            break;
        }
    }
    else if (key_type == LEFT)
    {
        entry->on_change(-1.0, false);
    }
    else if (key_type == RIGHT)
    {
        entry->on_change(1.0, true);
    }
}
