// Copyright ReGuider Team, 2016-2017
//
#include <librg/network.h>
#include <librg/events.h>
#include <librg/components/interpolable.h>
#include <librg/components/streamable.h>

void librg::entities_interpolate(double dt)
{
    entities->each<interpolable_t, transform_t, streamable_t>([dt](entity_t entity, interpolable_t& inter, transform_t& tran, streamable_t& stream) {
        auto lpos = inter.lastTransform.position;
        auto tpos = inter.targetTransform.position;

        inter.time += dt;
        auto t = (float)(inter.time / core::config.tick_delay);

        auto posx = HMM_Lerp(lpos.X, t, tpos.X);
        auto posy = HMM_Lerp(lpos.Y, t, tpos.Y);
        auto posz = HMM_Lerp(lpos.Z, t, tpos.Z);
        auto npos = hmm_vec3{ posx, posy, posz };

        // TODO: rot and scale

        // ...

        auto newTransform = transform_t(npos, tran.rotation, tran.scale);
        events::trigger(events::on_inter, new events::event_inter_t {
            entity.id().id(), entity, stream.type, newTransform
        });
    });
}
