#include <stdio.h>
#include <string.h>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>  // MessageID
#include <BuildVersion.h>
#include <MessageID.h>

#define SERVER_PORT 27010

int main(void)
{
    char str[512];

    RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
    RakNet::Packet *packet;

    RakNet::SocketDescriptor sd;
    peer->Startup(1,&sd, 1);

    printf("Enter server IP or hit enter for 127.0.0.1\n");
    gets(str);
    if (str[0]==0){
        strcpy(str, "127.0.0.1");
    }
    printf("Starting the client.\n");
    peer->Connect(str, SERVER_PORT, 0,0);

    while (1)
    {
        for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
        {
            switch (packet->data[0])
            {
            case ID_REMOTE_DISCONNECTION_NOTIFICATION:
                printf("Another client has disconnected.\n");
                break;
            case ID_REMOTE_CONNECTION_LOST:
                printf("Another client has lost the connection.\n");
                break;
            case ID_REMOTE_NEW_INCOMING_CONNECTION:
                printf("Another client has connected.\n");
                break;


            case ID_CONNECTION_REQUEST_ACCEPTED:
                {
                    printf("Our connection request has been accepted.\n");

                    // Use a BitStream to write a custom user message
                    // Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
                    RakNet::BitStream bsOut;
                    bsOut.Write((RakNet::MessageID)MessageID::CONNECTION_INIT);
                    bsOut.Write("Player name");
                    peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
                }
                break;

            case ID_NEW_INCOMING_CONNECTION:
                printf("A connection is incoming.\n");
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                printf("We have been disconnected.\n");
                break;
            case ID_CONNECTION_LOST:
                printf("Connection lost.\n");
                break;

            default:
                printf("Message with identifier %i has arrived.\n", packet->data[0]);
                break;
            }
        }
    }


    RakNet::RakPeerInterface::DestroyInstance(peer);

    return 0;
}
