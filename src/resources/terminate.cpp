#include <librg/core/shared.h>
#include <librg/resources.h>

using namespace librg;

void librg::resources_terminate()
{
    core::log("stopping resources");

    for (auto resource : resources::_resources) {
        resources::stop(resource.first);
    }
}
