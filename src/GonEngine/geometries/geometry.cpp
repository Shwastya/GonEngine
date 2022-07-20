#include "GonEngine/geometries/geometry.hpp"
#include <glm/detail/func_geometric.inl>
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glad/glad.h>


namespace gon {

    // Float pointer scoped
    // -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
    Geometry::ScpFloat::ScpFloat(const size_t length) 
        : m_data(new float[length])
    {} 
    void Geometry::ScpFloat::init(const size_t length)
    {
        m_data = new float[length];
    }

    Geometry::ScpFloat::~ScpFloat() { delete[] m_data; }

    float* Geometry::ScpFloat::get()
    {
        return m_data;
    }

    float& Geometry::ScpFloat::operator[](uint32_t idx)
    {
        return m_data[idx];
    }
    

    // Uint32_t pointer scoped
    // -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
    Geometry::ScpUint32::ScpUint32(const size_t length)
        : m_data(new uint32_t[length])
    {}
    void Geometry::ScpUint32::init(const size_t length)
    {
        m_data = new uint32_t[length];
    }
    Geometry::ScpUint32::~ScpUint32() { delete[] m_data; }

    uint32_t* Geometry::ScpUint32::get()
    {
        return m_data;
    }  

    uint32_t& Geometry::ScpUint32::operator[](uint32_t idx)
    {
        return m_data[idx];
    }
    
    // -*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-





    Geometry::Geometry(const uint32_t vertices, const uint32_t elements)
        : m_nVertices(vertices), m_nElements(elements)
    {}

    void Geometry::calcTangents(const float* positions, const float* uvs, const float* normals, float* tangents, float* biTangents) const
	{
        for (uint32_t i = 0; i < m_nVertices; i += 3)
        {
            const uint32_t idx3{ i * 3 };
            const uint32_t idx2{ i * 2 };

            glm::vec3 v0(positions[idx3 + 0], positions[idx3 + 1], positions[idx3 + 2]);
            glm::vec3 v1(positions[idx3 + 3], positions[idx3 + 4], positions[idx3 + 5]);
            glm::vec3 v2(positions[idx3 + 6], positions[idx3 + 7], positions[idx3 + 8]);

            glm::vec2 uv0(uvs[idx2 + 0], uvs[idx2 + 1]);
            glm::vec2 uv1(uvs[idx2 + 2], uvs[idx2 + 3]);
            glm::vec2 uv2(uvs[idx2 + 4], uvs[idx2 + 5]);

            glm::vec3 deltaPos1{ v1 - v0 };
            glm::vec3 deltaPos2{ v2 - v0 };

            glm::vec2 deltaUv1{ uv1 - uv0 };
            glm::vec2 deltaUv2{ uv2 - uv0 };

            float r{ 1 / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x) };
            glm::vec3 tangent{ (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * r };
            glm::vec3 biTangent{ (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * r };

            tangents[idx3 + 0] = tangents[idx3 + 3] = tangents[idx3 + 6] = tangent.x;
            tangents[idx3 + 1] = tangents[idx3 + 4] = tangents[idx3 + 7] = tangent.y;
            tangents[idx3 + 2] = tangents[idx3 + 5] = tangents[idx3 + 8] = tangent.z;

            biTangents[idx3 + 0] = biTangents[idx3 + 3] = biTangents[idx3 + 6] = biTangent.x;
            biTangents[idx3 + 1] = biTangents[idx3 + 4] = biTangents[idx3 + 7] = biTangent.y;
            biTangents[idx3 + 2] = biTangents[idx3 + 5] = biTangents[idx3 + 8] = biTangent.z;
        }

        for (uint32_t i = 0; i < m_nVertices; ++i)
        {
            const uint32_t idx3{ i * 3 };

            glm::vec3 n
            (
                (normals[idx3 + 0]), 
                (normals[idx3 + 1]), 
                (normals[idx3 + 2])
            );
            glm::vec3 t
            (
                tangents[idx3 + 0], 
                tangents[idx3 + 1], 
                tangents[idx3 + 2]
            );
            glm::vec3 b
            (
                biTangents[idx3 + 0], 
                biTangents[idx3 + 1], 
                biTangents[idx3 + 2]
            );

            t = glm::normalize(t - n * glm::dot(t, n));

            if (glm::dot(glm::cross(n, t), b) < 0.0f)
            {
                t = t * -1.0f;
            }

            tangents[idx3 + 0] = t.x;
            tangents[idx3 + 1] = t.y;
            tangents[idx3 + 2] = t.z;            
        }        
	}

	void Geometry::setData(const float* positions, const float* uvs, const float* normals, bool TangBitang)
	{
        const size_t length = static_cast<size_t>(m_nVertices) * 3;

        
        ScpFloat tangents(length);
        ScpFloat biTangents(length);       
        calcTangents(positions, uvs, normals, tangents.get(), biTangents.get());

        // en caso de la geometria de sphere o teapot
        // que no se calculan bien tangentes ni bitangentes
        if (!TangBitang)
        {
            memset(tangents.get(), 0, (length) * sizeof(float));
            memset(biTangents.get(), 0, (length) * sizeof(float));
        }

        uint32_t idx{ 0 };

        for (idx = 0; idx < m_nVertices * 3; idx += 3)
        {
            m_vbo[idx] = positions[idx]; m_vbo[idx + 1] = positions[idx + 1]; m_vbo[idx + 2] = positions[idx + 2];
        }

        uint32_t x = 0, y = idx;
        for (idx = idx; idx < (y + (m_nVertices * 2)); idx += 2)
        {
            //GON_WARN("vbo[{0}] = uvs[{1}];  vbo[{2}] = uvs[{3}]", idx, x, idx + 1, x + 1);
            m_vbo[idx] = uvs[x];  m_vbo[idx + 1] = uvs[x + 1];
            x += 2; 
        }

        x = 0, y = idx;
        for (idx = idx; idx < (y + (m_nVertices * 3)); idx += 3)
        {
            m_vbo[idx] = normals[x];  m_vbo[idx + 1] = normals[x + 1]; m_vbo[idx + 2] = normals[x + 2];
            x += 3;
        }

        x = 0, y = idx;
        for (idx = idx; idx < (y + (m_nVertices * 3)); idx += 3)
        {
            m_vbo[idx] = tangents[x];  m_vbo[idx + 1] = tangents[x + 1]; m_vbo[idx + 2] = tangents[x + 2];
            x += 3;
        }

        x = 0, y = idx;
        for (idx = idx; idx < (y + (m_nVertices * 3)); idx += 3)
        {
            m_vbo[idx] = biTangents[x];  m_vbo[idx + 1] = biTangents[x + 1]; m_vbo[idx + 2] = biTangents[x + 2];
            x += 3;
        }       
	}
}