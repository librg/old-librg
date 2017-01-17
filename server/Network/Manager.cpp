#include "../stdinc.h"

const short DEFAULT_SERVER_PORT = 27010;

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

            // TODO(inlife): move to settings.json
            mSocketDescriptor = RakNet::SocketDescriptor(DEFAULT_SERVER_PORT, 0);

            int maxplayers = 16;
            std::string password = "";

            if (mPeer->Startup(maxplayers, &mSocketDescriptor, 1) != RakNet::RAKNET_STARTED) {
                Core::Instance()->Log("Unable to startup server!");
                Core::Instance()->Log("Port might be already being used by another process!");
                return;
            }

            if (password.size() > 0) {
                mPeer->SetIncomingPassword(password.c_str(), password.size());
            }

            mPeer->SetMaximumIncomingConnections(maxplayers);
            mPeer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
        }

        void Manager::Update()
        {
            // // Use a BitStream to write a custom user message
            // // Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
            // RakNet::BitStream bsOut;
            // bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
            // bsOut.Write("Hello world");
            // mPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
        }

        void Manager::Receive()
        {
            RakNet::Packet* packet = nullptr;

            while ((packet = mPeer->Receive())) {

                switch (packet->data[0]) {
                    // case :
                }

                mPeer->DeallocatePacket(packet);
            }
        }
    }
}
