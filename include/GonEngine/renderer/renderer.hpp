#pragma once
#include "GonEngine/headers/h_renderer.hpp"

namespace Gon 	
{
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
	class  CubeMapText;
	class  Texture2D;	
	struct VBOLayout;
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	

	struct Renderer	{ // namespace commands

		Renderer()  = delete;
		~Renderer() = delete;

		static void init(const bool cullface, const bool depthtest, const bool alphablending);		
		static void reset();		

		static void init3D();
		static void reset3D();

		static void setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
		static void onWindowResize(const uint32_t width, const uint32_t height);						

		static void beginScene(const glm::mat4& view, const glm::mat4& projection);
		static void drawSkyBox(const CubeMapText* skybox);

		static void endScene();

		// 3D Renderer
		static void draw3D(const Geometry::Type Geo3D, glm::mat4& transform, texture2D albedo);

		

		static void drawReflect3D(vector3 t, vector4 r, vector3 s, const CubeMapText* text, vector3 camPos);
		static void drawRotateReflect3D(vector3 t, vector4 r, vector3 s, const CubeMapText* text, vector3 camPos);
		



	private:
		static void TRSsubmit();
	};
}