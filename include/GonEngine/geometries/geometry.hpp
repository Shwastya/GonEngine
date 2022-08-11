#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <cstdint>

namespace Gon {

    class Geometry
    {
    public:

        enum  Type
        {
            TRIANGLE = 0, QUAD, CUBE, SKYBOX
        };

        Geometry() = default;
        virtual ~Geometry() = default;

        Geometry(const Geometry&) = default;
        Geometry& operator=(const Geometry&) = default;

        Geometry(Geometry&&) noexcept = default;
        Geometry& operator=(Geometry&&) noexcept = default; 

        virtual void draw() = 0;

        static u_ptr<Geometry> create(Geometry::Type type, const float size);
        static u_ptr<Geometry> create(Geometry::Type type);
    };
}