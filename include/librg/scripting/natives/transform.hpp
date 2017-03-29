#ifndef _scripting_transform
#define _scripting_transform

#include <librg/components/transform.h>

namespace librg
{
    namespace scripting
    {
        inline static transform_create(uint64_t index)
        {
            auto entity = librg::entities->get((Entity::id)index);
            entity.assign<transform_t>();
        }

        inline static transform_get_position(uint64_t index)
        {
            auto entity = librg::entities->get((Entity::id)index);
            auto transform = entity.component<transform_t>();

            
        }
    }
}

#endif // _scripting_transform_h
