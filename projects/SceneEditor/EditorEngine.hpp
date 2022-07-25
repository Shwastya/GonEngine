#pragma once
#include "EditorLayer.hpp"

#include <GonEngine/main.h>

namespace gon {

	

	class EditorEngine : public GonEngine
	{
	public:

		/* (API | name | aspect - window | layers reserved) */
		EditorEngine();
		~EditorEngine();
	};
}