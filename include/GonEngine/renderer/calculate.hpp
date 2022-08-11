#pragma once
#include <cstdint>

namespace Gon
{
	void calculateTangents(const float* positions, const float* uvs, const float* normals, float* tangents, float* biTangents, const uint32_t count);

}