// Copyright ReGuider Team, 2016-2017
//
#include <librg/events.h>

using namespace librg;

void librg::events_initialize()
{
    
}

/**
 * Storage for event handlers
 */
std::unordered_map<uint64_t, std::vector<events::callback_t>> events::handlers;