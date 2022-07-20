#include "GonEngine/geometries/geometry.hpp"
#include <glm/detail/func_geometric.inl>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glad/glad.h>


namespace gon {

	void Geometry::calcTangents(const float* positions, const float* uvs, const float* normals, float* tangents, float* biTangents) const
	{
        for (size_t i = 0; i < _nVertices; i += 3)
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

        for (size_t i = 0; i < _nVertices; ++i)
        {
            const uint32_t idx3{ i * 3 };

            glm::vec3 n(normals[idx3 + 0], normals[idx3 + 1], normals[idx3 + 2]);
            glm::vec3 t(tangents[idx3 + 0], tangents[idx3 + 1], tangents[idx3 + 2]);
            glm::vec3 b(biTangents[idx3 + 0], biTangents[idx3 + 1], biTangents[idx3 + 2]);

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

	void Geometry::setData(const float* positions, const float* uvs, const float* normals, const uint32_t* indices, float* vbo, bool TangBitang)
	{
        const size_t length = static_cast<size_t>(_nVertices) * 3;
        const auto tangents = new float[length];
        const auto biTangents = new float[length];


        calcTangents(positions, uvs, normals, tangents, biTangents);
        // en caso de la geometria de sphere o teapot
        // que no se calculan bien tangentes ni bitangentes

        if (!TangBitang)
        {
            memset(tangents, 0.0f, length * sizeof(float));
            memset(biTangents, 0.0f, length * sizeof(float));
        }

        uint32_t idx{ 0 }, idxUvs{ 0 }, idxVbo{ 0 };

        for (size_t i = 0; i < _nVertices; i++)
        {
            vbo[idxVbo] = positions[idx];
            vbo[idxVbo + 1] = positions[idx + 1];
            vbo[idxVbo + 2] = positions[idx + 2];

            // uvs
            vbo[idxVbo + 3] = uvs[idxUvs];
            vbo[idxVbo + 4] = uvs[idxUvs + 1];
            idxUvs += 2;

            // normals
            vbo[idxVbo + 5] = normals[idx];
            vbo[idxVbo + 6] = normals[idx + 1];
            vbo[idxVbo + 7] = normals[idx + 2];

            // tangents
            vbo[idxVbo + 8] = tangents[idx];
            vbo[idxVbo + 9] = tangents[idx + 1];
            vbo[idxVbo + 10] = tangents[idx + 2];

            // bitangents
            vbo[idxVbo + 11] = biTangents[idx];
            vbo[idxVbo + 12] = biTangents[idx + 1];
            vbo[idxVbo + 13] = biTangents[idx + 2];

            idx += 3;
            idxVbo += 14;
        }
        delete[] tangents;
        delete[] biTangents;
	}

	

}