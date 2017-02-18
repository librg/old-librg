#ifndef __resource_manager
#define __resource_manager

#include <unordered_map>
#include <vector>
#include <uv.h>
#include <Utils/Singleton.h>

#include "Resource.h"

namespace Server    {
namespace Resource  {


class Manager : public Singleton<Manager>
{
    friend class Singleton<Manager>;

public:
    Manager();
    ~Manager();

    /**
     * Add new resource to the storage
     * @param name
     * @param resource
     */
    inline void Add(std::string name, Resource* resource) {
        mResources.insert(std::pair<std::string, Resource*>(name, resource));
    };

    /**
     * Check if resource exist
     * @param  name
     * @return state
     */
    inline bool Exist(std::string name) {
        try {
            return !!(mResources[name]);
        }
        catch (std::exception) {
            return false;
        }
    };

    /**
     * Get reseource by name or nullptr
     * @param  name
     * @return
     */
    inline Resource* Get(std::string name) {
        return this->Exist(name) ? mResources[name] : nullptr;
    }

    /**
     * Chwck if resource is running
     * @param  name
     * @return
     */
    inline bool IsRunning(std::string name) {
        return this->Exist(name) && this->Get(name)->IsRunning();
    };

    void Tick();

private:
    std::unordered_map<std::string, Resource*> mResources;
};


} // Resource
} // Server

#endif // __resource_manager
