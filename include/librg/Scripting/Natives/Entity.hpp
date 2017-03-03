#ifndef __entity_system
#define __entity_system

using namespace Sqrat;

namespace Server    {
namespace Scripting {

namespace Entity
{
    /**
     * Public API method for creating an entity.
     */
    inline static uint64_t entityCreate(Function callback)
    {
        entityx::Entity entity = Server::Entity::Manager::Instance()->create();
        return entity.id().id();
    }

    /**
     * Public API method for destroying an event.
     * @param index   An ID of the entity.
     */
    inline static void entityDestroy(uint64_t index)
    {
        Server::Entity::Manager::Instance()->get((entityx::Entity::Id)index).destroy();
    }

    /**
     * Registry method
     * @param table
     */
    inline static void Install(Table& table)
    {
        table.Func("entityCreate",  &entityCreate);
        table.Func("entityDestroy", &entityDestroy);
    }
}



} // Scripting
} // Server

#endif // __entity_system
