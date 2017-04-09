// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_components_streamable_h
#define librg_components_streamable_h

#include <librg/entities.h>
#include <librg/components/transform.h>

namespace librg
{
    struct streamable_t {
        streamable_t() : queryRange{ 250, 250, 250 }, ignoredEntities(), type(0) {}
        streamable_t(hmm_vec3 queryRange): queryRange(queryRange), ignoredEntities(), type(0) {}
        streamable_t(float x, float y, float z) : queryRange(hmm_vec3{ x,y,z }), ignoredEntities(), type(0) {}
        streamable_t(hmm_vec3 queryRange, uint8_t type): queryRange(queryRange), ignoredEntities(), type(type) {}
        hmm_vec3 queryRange;
        std::vector<Entity> ignoredEntities;
        uint8_t type;
    };
}

#endif // librg_components_streamable_h
