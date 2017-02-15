#ifndef __resource_manager
#define __resource_manager

#include <map>
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
    void AddResource(std::string name, Resource* resource);
    void Tick();

private:
    std::map<std::string, Resource*> mResources;
};


} // Resource
} // Server

#endif // __resource_manager
