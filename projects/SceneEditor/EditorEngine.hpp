#pragma once
#include "EditorLayer.hpp"

#include <GonEngine/main.h>

namespace Gon {

	struct Properties
	{
		const API Api			{ API::OpenGL };
		const std::string Name	{ "UI-Editor" };
		const int32_t Width		{ 600 };
		const int32_t Height	{ 800 };
		const size_t  Capacity	{ 1 };
	};

	static Properties* ThisProject;

	class EditorEngine : public GonEngine
	{
	public:
		EditorEngine();
		~EditorEngine();
	};
}