#pragma once
#include <cstdint>
#include <map>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {

	enum class DataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static const uint32_t typeSize(const DataType type) 
	{

		const uint32_t size  = sizeof(float); // == sizeof(int) = 4

		switch (type)
		{
			case DataType::Float:	return size;
			case DataType::Float2:	return size * 2;
			case DataType::Float3:	return size * 3;
			case DataType::Float4:	return size * 4;
			case DataType::Int:		return size;
			case DataType::Int2:	return size * 2;
			case DataType::Int3:	return size * 3;
			case DataType::Int4:	return size * 4;
			case DataType::Mat3:	return size * (3 * 3);
			case DataType::Mat4:	return size * (4 * 4);
			case DataType::Bool:	return 1;
		}
		GON_ASSERT(false, "Shader Data Type does not exist");
		return 0;
	}	

	struct BufferObject // VB...
	{
		BufferObject() = default;
		BufferObject(DataType type, const std::string& name, 
			const bool normalized = false)
			: m_name(name), 
			  m_type(type),
			  m_size(typeSize(type)),
			  m_offset(0),
			  m_normalized(normalized)
		{

		}

		BufferObject(const BufferObject&) = default;
		BufferObject& operator=(const BufferObject&) = default;

		BufferObject(BufferObject&&) noexcept = default;
		BufferObject& operator=(BufferObject&&) noexcept = default;

		const uint32_t compCount() const
		{
			switch (m_type)
			{
				case DataType::Float:	return 1;
				case DataType::Float2:	return 2;
				case DataType::Float3:	return 3;
				case DataType::Float4:	return 4;
				case DataType::Int:		return 1;
				case DataType::Int2:	return 2;
				case DataType::Int3:	return 3;
				case DataType::Int4:	return 4;
				case DataType::Mat3:	return (3 * 3);
				case DataType::Mat4:	return (4 * 4);
				case DataType::Bool:	return 1;

			}
			GON_ASSERT(false, "Shader Data Type does not exist");
			return 0;
		}

		std::string m_name;
		DataType m_type;
		uint64_t m_offset;
		uint32_t m_size;
		bool m_normalized;
	};



	struct VBOLayout
	{
		VBOLayout() = default;

		VBOLayout(const std::initializer_list<BufferObject>& objects)
			: m_objects(objects)
		{
			CalculateOffsetAndStride();
			GON_TRACE("[CREATED] VBO Layout, uploading to VAO the VBO components...");
		}

		inline uint32_t stride() const { return m_stride; }
		inline const std::vector<BufferObject>& getObjects() const { return m_objects; }


		std::vector<BufferObject>::iterator begin() { return m_objects.begin(); }
		std::vector<BufferObject>::iterator end()	{ return m_objects.end(); }


	private:

		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& object : m_objects)
			{
				object.m_offset = offset;
				offset += object.m_size;
				m_stride += object.m_size;
			}
		}
	private:
		std::vector<BufferObject> m_objects;
		uint32_t m_stride = 0;
	};
}
