#include <librg/network.h>
#include <librg/core/shared.h>

using namespace librg;

/**
 * Storage for use tick callback
 */
std::function<void(double)> callback = nullptr;

/**
 * Setup default mode (server)
 */
core::rgmode current_mode = core::mode_server;

/**
 * Main ticker method
 */
void core::tick() {
    if (callback) {
        callback(0.016); //delta =  get current time - lasttime
    }

    network::update();
}

/**
 * Set mode of execution
 * @param mode
 */
void core::set_mode(core::rgmode mode) {
    current_mode = mode;
}

/**
 * Get current mode of exectution
 * @return
 */
core::rgmode core::get_mode() {
    return current_mode;
}

/**
 * Set user ticker callaack
 * (subscribing)
 * @param cb
 */
void core::set_tick_cb(std::function<void(double)> cb) {
    callback = cb;
}

/**
 * Main polling method
 */
void core::poll() {
    network::receive();
}
