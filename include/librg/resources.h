#ifndef __resources
#define __resources

#include <uv.h>
#include <vector>
#include <unordered_map>

#include "resource.h"

namespace librg
{
    namespace resources
    {
        /**
         * Add new resource to the storage
         * @param name
         * @param resource
         */
        static inline void add(std::string name, Resource* resource) {
            __resources.insert(std::pair<std::string, Resource*>(name, resource));
        };

        /**
         * Check if resource exists
         * @param  name
         * @return state
         */
        static inline bool exists(std::string name) {
            return !(__resources.find(name) == __resources.end());
        };

        /**
         * Get reseource by name or nullptr
         * @param  name
         * @return
         */
        static inline Resource* get(std::string name) {
            return this->exist(name) ? __resources[name] : nullptr;
        };

        /**
         * Chwck if resource is running
         * @param  name
         * @return
         */
        static inline bool running(std::string name) {
            return this->exist(name) && this->get(name)->running();
        };

        static void initialize();
        static void deinitialize();

        std::unordered_map<std::string, Resource*> __resources;
    }
}

#endif // __resources
