// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>
#include <librg/components/interpolable.h>
#include <librg/components/streamable.h>

void librg::network::interpolate(double dt)
{
    entities->each<interpolable_t, transform_t>([dt](entity_t entity, interpolable_t& inter, transform_t& tran) {
        auto lpos = inter.lastTransform.position;
        auto tpos = inter.targetTransform.position;
        auto  t = inter.time + dt;
        inter.time += dt;

        auto posx = HMM_Lerp(lpos.X, t, tpos.X);
        auto posy = HMM_Lerp(lpos.Y, t, tpos.Y);
        auto posz = HMM_Lerp(lpos.Z, t, tpos.Z);
        auto npos = hmm_vec3{ posx, posy, posz };

        // TODO: rot and scale

        // ...

        tran.position = npos;
        inter.lastTransform = tran;
    });
}