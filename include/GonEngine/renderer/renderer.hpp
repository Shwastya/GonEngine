#pragma once
#include "GonEngine/headers/h_renderer.hpp"

namespace Gon 	
{
	enum  Geo
	{
		TRIANGLE = 0,
		QUAD = 1,
		CUBE = 2,
		BLEENDIG = QUAD,
		SKYBOX = 3
	};	
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

		static VBOLayout getLayout();

		// 3D Renderer
		static void draw3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void draw3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void draw3D(const Geo Geo3D, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void draw3D(const Geo Geo3D, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		static void drawRotate3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotate3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotate3D(const Geo Geo3D, VEC4 r, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		static void drawPolygon3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Geo Geo3D, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Geo Geo3D, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		static void drawRotatePolygon3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotatePolygon3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotatePolygon3D(const Geo Geo3D, VEC4 r, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		static void drawBlending(VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawBlending(VEC3 t, VEC3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });


	private:
		static void TRSsubmit();
	};
}