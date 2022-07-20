#pragma once
#include <cstdint>

namespace gon {


    class Geometry
    {

    public:
        Geometry() = default;
        virtual ~Geometry() = default;

        Geometry(const Geometry&) = default;
        Geometry& operator=(const Geometry&) = default;

        Geometry(Geometry&&) noexcept = default;
        Geometry& operator=(Geometry&&) noexcept = default;

    protected:
        struct ScpTangent
        {
            ScpTangent(const size_t size)
            {

            }

        };

    protected:
        void calcTangents(const float* positions, const float* uvs,
            const float* normals, float* tangents, float* biTangents) const;

        void setData(const float* positions, const float* uvs,
            const float* normals, const uint32_t* indices, float* vbo,
            bool TangBitang = true);

    protected:

        uint32_t _nVertices{ 0 };
        uint32_t _nElements{ 0 };
    };
}