#pragma once
#define N_V static_cast<size_t>(m_nVertices) 
#include <cstdint>
#include <iostream>

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
            
            // overload operators
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
            // overload operator            
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

        uint32_t m_nVertices{ 0 };
        uint32_t m_nElements{ 0 };
        //const std::string m_name{ nullptr };
    };
}