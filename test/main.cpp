// #include <librg/entities.h>
// #include "test.hpp"

// namespace Server  {
// namespace Entity  {
// namespace Test    {


// void RunTest()
// {
//     TEST("Entity Management");
//     {
//         IT("should create 2 entities.") {
//             auto entity = Manager::Instance()->create();
//             auto entity2 = Manager::Instance()->create();
//             auto id = entity2.id().id();

//             EXPECT(id != 0);
//         }

//         IT("should destroy an entity.") {
//             auto entity = Manager::Instance()->create();

//             entity.destroy();

//             EXPECT(entity == 0);
//         }
//     }
// }


// } // Test
// } // Entity
// } // Server
// // TODO(zaklaus): I really hate these ^^, we should consider making it nested
// // Server::Event::Test, as soon as the major linux distros get more recent GCC version, since 4.x.x doesn't support C++1z at all.
// //

#include <clocale>
#include "utils/fs.hpp"
#include "utils/aabb.hpp"
#include "streamer.hpp"
#include "events.hpp"

int main()
{
    #ifdef WIN32
        // Set our locale to the C locale, as Unicode output only functions in this locale
        std::setlocale(LC_ALL, "C");
        SetConsoleOutputCP(CP_UTF8);
    #endif

    motd();

    {
        fs_test();
        aabb_test();

        streamer_test();
        events_test();
    }

    return results();
}
