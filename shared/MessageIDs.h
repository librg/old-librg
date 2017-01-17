#pragma once

#include "MessageIdentifiers.h"

namespace MessageIDs
{
    enum MainCategoryIDs
    {
        MOID_CONNECTION = ID_USER_PACKET_ENUM + 1,
        MOID_SYNC,
        MOID_EVENT,
    };

    enum ConnectionCategoryIDs
    {
        MOID_CONNECTION_INIT,
        MOID_CONNECTION_REFUSED,
        MOID_CONNECTION_ACCEPTED,
        MOID_CONNECTION_DISCONNECTED,
    };

    enum SyncCategoryIDs
    {
        MOID_SYNC_ONFOOT,
    };

    enum EventCategoryIDs
    {
        MOID_PLAYER_CREATE,
    };
};
