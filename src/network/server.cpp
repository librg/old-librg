#include <librg/network.h>
#include <librg/core/shared.h>

using namespace librg;

/**
 * Server intializer code
 * sets up RakNet and starts
 * all network activty
 */
void network::server(int port)
{
    core::log("initializing network...");

    // TODO(inlife): move to settings.json
    network::data.socket_descriptor = RakNet::SocketDescriptor(port, 0);

    int maxplayers = 16;
    std::string password = "";

    if (network::data.peer->Startup(maxplayers, &network::data.socket_descriptor, 1) != RakNet::RAKNET_STARTED) {
        core::log("Unable to startup server!");
        core::log("Port might be already being used by another process!");
        return;
    }

    if (password.size() > 0) {
        network::data.peer->SetIncomingPassword(password.c_str(), password.size());
    }

    network::data.peer->SetMaximumIncomingConnections(maxplayers);
    network::data.peer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
}
