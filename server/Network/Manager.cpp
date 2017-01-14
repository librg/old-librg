#include "../stdinc.h"

namespace MOServer
{
    namespace Network
    {

        Manager::Manager()
        {
            mPeer = RakNet::RakPeerInterface::GetInstance();
        }

        Manager::~Manager()
        {
            mPeer->Shutdown( 500 );
            RakNet::RakPeerInterface::DestroyInstance( mPeer );
        }

        void Manager::Init()
        {
            Core::Instance()->Log("initializing network...");

            mSocketDescriptor = RakNet::SocketDescriptor(27015, 0);

            int maxplayers = 16;
            std::string password = "";

            if (mPeer->Startup(maxplayers, &mSocketDescriptor, 1) != RakNet::RAKNET_STARTED) {
                Core::Instance()->Log("Unable to startup server !\n Port might be already being used by another process !");
            }

            if (password.size() > 0) {
                mPeer->SetIncomingPassword(password.c_str(), password.size());
            }

            mPeer->SetMaximumIncomingConnections(maxplayers);
            mPeer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
        }

        void Manager::Update()
        {

        }

        void Manager::Receive()
        {
            RakNet::Packet* packet = nullptr;

            while ((packet = mPeer->Receive())) {

                // add packet handling

                mPeer->DeallocatePacket(packet);
            }
        }
    }
}
