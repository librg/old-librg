// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_components_client_h
#define librg_components_client_h

#include <string>
#include <unordered_map>

namespace librg
{
    struct client_t {
        client_t(RakNet::SystemAddress a, std::string n, std::string s) : address(a), nickname(n), serial(s), last_snapshot() {}

        RakNet::SystemAddress address;
        std::string nickname;
        std::string serial;

        std::unordered_map<uint64_t, bool> last_snapshot;
    };
}

#endif // librg_components_client_h
