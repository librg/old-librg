﻿// Copyright ReGuider Team, 2016-2017
//
#include <librg/streamer.h>

void librg::streamer::qtree_t::subdivide()
{
    using namespace vectorial;

    vec3f hd = boundary.halfdim / 2.f;

    auto nwc = vec3f(boundary.center.x() - hd.x(), boundary.center.y() - hd.y(), .0f);
    auto nwb = aabb_t(nwc, hd);
    auto nec = vec3f(boundary.center.x() + hd.x(), boundary.center.y() - hd.y(), .0f);
    auto neb = aabb_t(nec, hd);
    auto swc = vec3f(boundary.center.x() - hd.x(), boundary.center.y() + hd.y(), .0f);
    auto swb = aabb_t(swc, hd);
    auto sec = vec3f(boundary.center.x() + hd.x(), boundary.center.y() + hd.y(), .0f);
    auto seb = aabb_t(sec, hd);

    create_child(nwb);
    create_child(neb);
    create_child(swb);
    create_child(seb);
}
