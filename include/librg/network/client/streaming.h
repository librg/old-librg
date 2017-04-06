// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_client_streaming_hpp
#define librg_network_client_streaming_hpp

#include <vectorial/vectorial.h>

#include <librg/core.h>
#include <librg/network.h>
#include <librg/streamer.h>

namespace librg
{
    namespace network
    {
        void client_streamer_entity_sync(RakNet::Packet* packet);
    }
}

#endif // librg_network_client_streaming_hpp
