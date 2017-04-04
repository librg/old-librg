// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_client_streaming_hpp
#define librg_network_client_streaming_hpp

#include <librg/network.h>
#include <vectorial/vectorial.h>
#include <librg/streamer.h>
#include <librg/core/shared.h>

namespace librg
{
    namespace network
    {
        void client_streamer_entity_sync(RakNet::Packet* packet);
    }
}

#endif // librg_network_client_streaming_hpp
