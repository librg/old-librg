#ifndef __resource_manager
#define __resource_manager

#include <uv.h>
#include <vector>

#include <Utils/Singleton.h>

namespace Server    {
namespace Resource  {


class Manager : public Singleton<Manager>
{
    friend class Singleton<Manager>;

public:
    Manager();
    ~Manager();
    void Init();
    void Tick();

private:

};


} // Resource
} // Server

#endif // __resource_manager
