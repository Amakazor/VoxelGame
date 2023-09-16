#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <ranges>

enum message_type
{
    key_action,
    mouse_movement,
};

class message_bus
{
protected:
    inline static std::shared_ptr<message_bus> instance_ = nullptr;
    
    template <typename T>
    static inline std::map<message_type, std::map<std::string, std::function<void(T)>>> handlers_ = {};
    
public:
    message_bus() = default;

    static std::shared_ptr<message_bus> get_instance();

    template <typename T>
    void register_handler(message_type type, const std::string& key, std::function<void(T)> handler);

    template <typename T>
    void unregister_handler(message_type type, const std::string& key);

    template <typename T>
    void message(message_type type, T message);
};

template <typename T>
void message_bus::register_handler(const message_type type, const std::string& key, std::function<void(T)> handler)
{
    if (!handlers_<T>.contains(type)) handlers_<T>[type] = {};
    handlers_<T>[type].insert({key, handler});
}

template <typename T>
void message_bus::unregister_handler(const message_type type, const std::string& key)
{
    if (!handlers_<T>.contains(type)) return;
    handlers_<T>[type].erase(key);
}

template <typename T>
void message_bus::message(const message_type type, const T message)
{
    if (!handlers_<T>.contains(type)) return;
    for (auto& handler : handlers_<T>[type] | std::views::values) handler(message);
}