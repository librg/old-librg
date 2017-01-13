#include "../stdinc.h"

// using namespace MOServer;

namespace MOServer
{
    namespace Network
    {

        Manager::Manager()
        {

        }

        Manager::~Manager()
        {

        }

        void Manager::Init()
        {
            Core::Instance()->Log("initializing network...");
        //     ServerProperties serverProperies = Core::GetCore()->GetServerProperties();
        //     mSocketDescriptor = RakNet::SocketDescriptor(serverProperies.mServerPort, 0);
        //     mPeer = RakNet::RakPeerInterface::GetInstance();

        //     if (mPeer->Startup(serverProperies.mMaxPlayers, &mSocketDescriptor, 1) != RakNet::RAKNET_STARTED)
        //     {
        //         Core::GetCore()->Log("Unable to startup server !\n Port might be already being used by another process !");
        //     }

        //     if (serverProperies.mPassword.size() > 0)
        //     {
        //         mPeer->SetIncomingPassword(serverProperies.mPassword.c_str(), serverProperies.mPassword.size());
        //     }

        //     mPeer->SetMaximumIncomingConnections(serverProperies.mMaxPlayers);
        //     mPeer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
        }

        void Manager::Update()
        {

        }

        void Manager::Receive()
        {
            for (RakNet::Packet* packet = mPeer->Receive(); packet; mPeer->DeallocatePacket(packet), packet = mPeer->Receive())
            {

                // switch (packet->data[0])
                // {
                //     case MessageIDs::LHMPID_CONNECTION:
                //     {
                //         ServerConnectionHandler Handler(&mClients);
                //         Handler.ProcessMessage(this, packet);
                //     }
                //     break;
                //     case MessageIDs::LHMPID_SYNC:
                //     {
                //         ServerSyncHandler Handler(&mClients);
                //         Handler.ProcessMessage(this, packet);
                //     }
                //     default:
                //     {
                //         ServerRakNetHandler Handler(&mClients);
                //         Handler.ProcessMessage(this, packet);
                //     }
                //     break;
                // }
            }
        }
    }
}
