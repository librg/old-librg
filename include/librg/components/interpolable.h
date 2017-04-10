// Copyright ReGuider Team, 2016-2017
//
#ifndef librg_components_interpolable_h
#define librg_components_interpolable_h

#include <librg/entities.h>
#include <librg/components/transform.h>
#include <chrono>

namespace librg
{
    using namespace std::chrono;
    struct interpolable_t {
        interpolable_t(transform_t tran) : time(), targetTransform(tran), lastTransform(tran) {}
        double time;
        transform_t targetTransform;
        transform_t lastTransform;
    };
}

#endif // librg_components_interpolable_h
