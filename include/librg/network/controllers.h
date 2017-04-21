// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_network_controllers_h
#define librg_network_controllers_h

#include <librg/network.h>

namespace librg
{
    namespace network
    {
        namespace connection_controller
        {
            void init       (peer_t*, packet_t*, uint8_t);
            void request    (peer_t*, packet_t*, uint8_t);
            void refuse     (peer_t*, packet_t*, uint8_t);
            void accept     (peer_t*, packet_t*, uint8_t);
            void disconnect (peer_t*, packet_t*, uint8_t);
        }

        namespace entity_controller
        {
            void create     (peer_t*, packet_t*, uint8_t);
            void update     (peer_t*, packet_t*, uint8_t);
        }
    }
}

#endif // librg_network_controllers_h
