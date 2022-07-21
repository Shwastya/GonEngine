#pragma once
#define N_V static_cast<size_t>(m_nVertices) 
#include <cstdint>
#include <iostream>

namespace gon {


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

            ScpFloat() = default;
            ScpFloat(const size_t  length);
            void init(const size_t length);
            ~ScpFloat();

            float* get();
            
            // overload operators
            float& operator[](uint32_t idx);

        private:
            float* m_data{ nullptr };        
        };
        struct ScpUint32
        {
        public:

            ScpUint32() = default;
            ScpUint32(const size_t length);
            void init(const size_t length);
            ~ScpUint32();

            uint32_t* get();
            // overload operator            
            uint32_t& operator[](uint32_t idx);

        private:
            uint32_t* m_data{ nullptr };
        };

    protected:

        void calcTangents(const float* positions, const float* uvs,
            const float* normals, float* tangents, float* biTangents) const;

        void setData(const float* positions, const float* uvs,
            const float* normals, bool TangBitang = true);

    protected:

        uint32_t m_nVertices{ 0 };
        uint32_t m_nElements{ 0 };
        ScpFloat  m_vbo;
        //const std::string m_name{ nullptr };
    };
}