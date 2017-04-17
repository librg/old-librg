// // Copyright ReGuider Team, 2016-2017
// //
// #include <librg/core.h>
// #include <librg/network.h>

// using namespace librg;

// /**
//  * Server intializer code
//  * sets up RakNet and starts
//  * all network activty
//  */
// void network::server(int port)
// {
//     core::log("starting server at port: %d", port);

//     // // TODO(inlife): move to settings.json
//     // network::data.socket_descriptor = RakNet::SocketDescriptor(port, 0);

//     // int maxplayers = 16;
//     // std::string password = "";

//     // if (network::data.peer->Startup(maxplayers, &network::data.socket_descriptor, 1) != RakNet::RAKNET_STARTED) {
//     //     core::log("unable to startup server!");
//     //     core::log("port might be already being used by another process.");
//     //     return;
//     // }

//     // if (password.size() > 0) {
//     //     network::data.peer->SetIncomingPassword(password.c_str(), (int)password.size());
//     // }

//     // network::data.peer->SetMaximumIncomingConnections(maxplayers);
//     // network::data.peer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);


//     if (core::is_server()) {
//         // /* Bind the server to the default localhost.     */
//         // /* A specific host address can be specified by   */
//         // /* enet_address_set_host (& address, "x.x.x.x"); */
//         // address.host = ENET_HOST_ANY;
//         // /* Bind the server to port 1234. */
//         // address.port = 1234;
//         // server = enet_host_create (& address /* the address to bind the server host to */, 
//         //                              32       allow up to 32 clients and/or outgoing connections ,
//         //                               2      /* allow up to 2 channels to be used, 0 and 1 */,
//         //                               0      /* assume any amount of incoming bandwidth */,
//         //                               0      /* assume any amount of outgoing bandwidth */);
//         // if (server == NULL) {
//         //     core::error("An error occurred while trying to create an ENet server host.");
//         //     exit(EXIT_FAILURE);
//         // }
//     }
// }
