#include "input_handler.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>
#include "../messages/message_bus.h"
#include "../messages/key_message.h"

struct key_message;

void input_handler::handle_key_action(const key_message& message)
{
    if (message.action == GLFW_PRESS) pressed_keys_.insert(message.key);
    if (message.action == GLFW_RELEASE) pressed_keys_.erase(message.key);
}

void input_handler::handle_mouse(const mouse_message& message)
{
    if (!message.raw) return;

    mouse_movement_ = vector2(static_cast<float>(message.dx), static_cast<float>(message.dy));
    mouse_valid_ = true;
}

void input_handler::tick()
{
    inputs_.clear();

    if (pressed_keys_.contains(GLFW_KEY_W)) inputs_[forward] = 1.0f;
    else if (pressed_keys_.contains(GLFW_KEY_S)) inputs_[forward] = -1.0f;
    else inputs_[forward] = 0.0f;
    
    if (pressed_keys_.contains(GLFW_KEY_A)) inputs_[horizontal] = -1.0f;
    else if (pressed_keys_.contains(GLFW_KEY_D)) inputs_[horizontal] = 1.0f;
    else inputs_[horizontal] = 0.0f;
    
    if (pressed_keys_.contains(GLFW_KEY_SPACE)) inputs_[vertical] = 1.0f;
    else if (pressed_keys_.contains(GLFW_KEY_LEFT_SHIFT)) inputs_[vertical] = -1.0f;
    else inputs_[vertical] = 0.0f;

    if (mouse_valid_)
    {
        inputs_[mouse_x] = std::clamp(mouse_movement_.x, -500.0f, 500.0f);
        inputs_[mouse_y] = std::clamp(mouse_movement_.y, -500.0f, 500.0f);
        mouse_valid_ = false;
    }
    else
    {
        inputs_[mouse_x] = 0.0f;
        inputs_[mouse_y] = 0.0f;
    }
}

std::shared_ptr<input_handler> input_handler::get_instance()
{
    if (!instance_) instance_ = std::make_shared<input_handler>();
    return instance_;
}

float input_handler::get_input(const input_axes key)
{
    if (inputs_.contains(key)) return inputs_[key];
    return 0.0f;
}

input_handler::input_handler()
{
    std::cout << "input_handler::input_handler()" << std::endl;
    
    message_bus::get_instance()->register_handler<key_message>(key_action, "key_action", [this](const key_message& message) { handle_key_action(message); });
    message_bus::get_instance()->register_handler<mouse_message>(mouse_movement, "mouse_movement", [this](const mouse_message& message) { handle_mouse(message); });
}

input_handler::~input_handler()
{
    std::cout << "input_handler::~input_handler()" << std::endl;
    
    message_bus::get_instance()->unregister_handler<key_message>(key_action, "key_action");
    message_bus::get_instance()->unregister_handler<mouse_message>(mouse_movement, "mouse_movement");
}
