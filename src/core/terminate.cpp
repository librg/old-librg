// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/entities.h>
#include <librg/events.h>
#include <librg/network.h>
#include <librg/resources.h>
#include <librg/streamer.h>

void librg::core_terminate()
{
    librg::streamer_terminate();
    librg::entities_terminate();
    librg::events_terminate();
    librg::network_terminate();
    librg::resources_terminate();
}
