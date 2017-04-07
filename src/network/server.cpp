// Copyright ReGuider Team, 2016-2017
//
#include <librg/core.h>
#include <librg/network.h>

using namespace librg;

/**
 * Server intializer code
 * sets up RakNet and starts
 * all network activty
 */
void network::server(int port)
{
    core::log("starting server at port: %d", port);

    // TODO(inlife): move to settings.json
    network::data.socket_descriptor = RakNet::SocketDescriptor(port, 0);

    int maxplayers = 16;
    std::string password = "";

    if (network::data.peer->Startup(maxplayers, &network::data.socket_descriptor, 1) != RakNet::RAKNET_STARTED) {
        core::log("unable to startup server!");
        core::log("port might be already being used by another process.");
        return;
    }

    if (password.size() > 0) {
        network::data.peer->SetIncomingPassword(password.c_str(), (int)password.size());
    }

    network::data.peer->SetMaximumIncomingConnections(maxplayers);
    network::data.peer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
}
