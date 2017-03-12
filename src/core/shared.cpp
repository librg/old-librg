#include <librg/core/shared.h>

using namespace librg;

std::function<void(double)> callback = nullptr;
// int lasttime = 0;

void core::tick()
{
    if (callback) {
        callback(0.016); //delta =  get current time - lasttime
    }

    network::update();
}

void core::poll()
{
    network::receive();
}

void core::set_tick_cb(std::function<void(double)> cb)
{
    callback = cb;
}
