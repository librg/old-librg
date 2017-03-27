#ifndef _scripting_streamer
#define _scripting_streamer

#include <librg/streamer.h>

namespace librg
{
    namespace scripting
    {
        inline static void streamer_set_visible(uint64_t index, bool state)
        {
            auto entity = librg::entities->get((Entity::Id)index);
            librg::streamer::set_visible(entity, state);
        }

        inline static void streamer_set_visible_for(uint64_t index, uint64_t targetIndex, bool state)
        {
            auto entity = librg::entities->get((Entity::Id)index);
            auto target = librg::entities->get((Entity::Id)targetIndex);
            librg::streamer::set_visible_for(target, entity, state);
        }

        inline static void streamer_install(Sqrat::Table& table)
        {
            table.Func("streamerSetVisible", &streamer_set_visible);
            table.Func("streamerSetVisibleFor", &streamer_set_visible_for);
        }
    }
}

#endif // _scripting_streamer
