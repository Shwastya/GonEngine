#pragma once
#include "ExampleLayer.hpp"

#include <GonEngine/main.h>

namespace gon {

	

	class ExampleEngine : public GonEngine
	{
	public:

		/* (API | name | aspect - window | layers reserved) */
		ExampleEngine();
		~ExampleEngine();
	};
}