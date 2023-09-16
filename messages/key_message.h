#pragma once
#include <string>

#include "message.h"

struct key_message final :  message
{
    int32_t key;
    int32_t scancode;
    int32_t action;

    key_message(const int32_t key, const int32_t scancode, const int32_t action) : key(key), scancode(scancode), action(action) {}
};
