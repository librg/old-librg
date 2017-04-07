// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/entities.h>
#include <librg/events.h>
#include <librg/network.h>
#include <librg/resources.h>
#include <librg/streamer.h>

void librg::core_initialize(librg::mode mode)
{
    librg::entities_initialize();
    librg::events_initialize();
    librg::network_initialize();
    librg::resources_initialize();
    librg::streamer_initialize();

    librg::core::set_mode(mode);
}
