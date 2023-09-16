#include "message_bus.h"

std::shared_ptr<message_bus> message_bus::get_instance()
{
    if (!instance_) instance_ = std::make_shared<message_bus>();
    return instance_;
}
