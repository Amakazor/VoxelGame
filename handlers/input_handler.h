#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <GLFW/glfw3.h>
#include "../messages/key_message.h"
#include "../messages/mouse_message.h"
#include "../primitives/vector2.h"

enum input_axes
{
    horizontal,
    vertical,
    forward,
    mouse_x,
    mouse_y,
};

class input_handler
{
    inline static std::shared_ptr<input_handler> instance_ = nullptr;

    std::set<int32_t> pressed_keys_ = {};
    vector2 mouse_movement_ = {};
    bool mouse_valid_ = false;
    
    std::map<input_axes, float> inputs_ = {};

    void handle_key_action(const key_message& message);

    void handle_mouse(const mouse_message& message);

public:
    input_handler();
    ~input_handler();
    
    void tick();
    
    static std::shared_ptr<input_handler> get_instance();

    float get_input(input_axes key);
};
