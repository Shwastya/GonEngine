#pragma once
#define N_V static_cast<size_t>(m_nVertices) 
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <cstdint>

namespace Gon {

    class Geometry
    {

    public:

        Geometry(const uint32_t vertices, const uint32_t elements);
        virtual ~Geometry() = default;

        Geometry(const Geometry&) = default;
        Geometry& operator=(const Geometry&) = default;

        Geometry(Geometry&&) noexcept = default;
        Geometry& operator=(Geometry&&) noexcept = default;       

    protected:

        // RAII patterns
        struct ScpFloat
        {   
        public:

            ScpFloat();
            void init(const size_t length);
            ~ScpFloat();

            float* get() const;
            
            float& operator[](uint32_t idx);

        private:
            float* m_data{ nullptr };        
        };
        struct ScpUint32
        {
        public:

            ScpUint32();
            void init(const size_t length);
            ~ScpUint32();

            uint32_t* get() const;
                  
            uint32_t& operator[](uint32_t idx);

        private:
            uint32_t* m_data{ nullptr };
        };

    protected:

        void calcTangents(const float* positions, const float* uvs,
            const float* normals, float* tangents, float* biTangents) const;

        void setData(float* vbo, const float* positions, const float* uvs,
            const float* normals, bool TangBitang = true);

    protected:
        
        u_ptr<VAO> m_vao;
        uint32_t m_nVertices{ 0 };
        uint32_t m_nElements{ 0 };
    };
}