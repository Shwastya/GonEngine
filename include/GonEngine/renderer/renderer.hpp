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
		static void draw3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void draw3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void draw3D(const Geometry::Type Geo3D, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void draw3D(const Geometry::Type Geo3D, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });

		static void drawRotate3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawRotate3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawRotate3D(const Geometry::Type Geo3D, vector4 r, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });

		static void drawPolygon3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Geometry::Type Geo3D, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Geometry::Type Geo3D, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });

		static void drawRotatePolygon3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawRotatePolygon3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawRotatePolygon3D(const Geometry::Type Geo3D, vector4 r, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });

		static void drawBlending(vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });
		static void drawBlending(vector3 t, vector3 s, texture2D albedo, vector4 colormask = glm::vec4{ 1.0f });


	private:
		static void TRSsubmit();
	};
}