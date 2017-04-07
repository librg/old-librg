// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/network.h>

using namespace librg;

/**
 * Setup default mode (server)
 */
core::mode current_mode = core::mode_server;

/**
 * Main ticker method
 */
void core::tick() {
    if (callback) {
        callback(0.016); //delta =  get current time - lasttime
    }

    if (current_mode == core::mode_server) {
        network::update();
    }
}

/**
 * Set mode of execution
 * @param mode
 */
void core::set_mode(core::mode mode) {
    current_mode = mode;
}

/**
 * Get current mode of exectution
 * @return
 */
core::mode core::get_mode() {
    return current_mode;
}

/**
 * Main polling method
 */
void core::poll() {
    network::receive();
}
