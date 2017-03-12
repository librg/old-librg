#ifndef __scripting_entity
#define __scripting_entity

#include <librg/entities.h>

using namespace Sqrat;

namespace librg
{
    namespace scripting
    {
        /**
         * Public API method for creating an entity.
         */
        inline static uint64_t entity_create(Function callback)
        {
            entityx::Entity entity = librg::entities->create();
            return entity.id().id();
        }

        /**
         * Public API method for destroying an event.
         * @param index   An ID of the entity.
         */
        inline static void entity_destroy(uint64_t index)
        {
            librg::entities->get((entityx::Entity::Id)index).destroy();
        }

        /**
         * Registry method
         * @param table
         */
        inline static void entity_install(Table& table)
        {
            table.Func("entityCreate",  &entity_create);
            table.Func("entityDestroy", &entity_destroy);
        }
    }
}

#endif // __scripting_entity
