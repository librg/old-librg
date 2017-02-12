#ifndef __resource_scripting_manager
#define __resource_scripting_manager

namespace Server::Scripting::Resource  {


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
// } // Scripting
// } // Server

#endif // __resource_scripting_manager
