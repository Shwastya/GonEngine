#pragma once
#include "GonEngine/renderer/renderer.hpp"

namespace Gon {

	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	struct	VBOLayout;
	class	Texture2D;
	class	Shader;
	struct	VAO;
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	
	class Renderer3D
	{
	public:

		Renderer3D()  = delete;
		~Renderer3D() = delete;

		static VBOLayout getLayout();
		static void init();
		static void reset();

		static void beginScene();
		static void beginScene(const glm::mat4& view, const glm::mat4& projection);
		static void TRSsubmit();
		static void endScene();

		// Quad
		static void drawQuad(Vec3 t, Vec4 r, Vec3 s, Texture albedo);
		static void drawQuad(Vec4 r, Vec3 s, Texture albedo);
		static void drawQuad(Vec3 s, Texture albedo);
		static void drawQuad(Texture albedo);
		static void drawRotateQuad(Vec3 t, Vec4 r, Vec3 s, Texture albedo);
		static void drawRotateQuad(Vec4 r, Vec3 s, Texture albedo);
		static void drawRotateQuad(Vec4 r, Texture albedo);
		// Cube
		static void drawCube(Vec3 t, Vec4 r, Vec3 s, Texture albedo);
		static void drawCube(Vec4 r, Vec3 s, Texture albedo);
		static void drawCube(Vec3 s, Texture albedo);
		static void drawCube(Texture albedo);
		static void drawRotateCube(Vec3 t, Vec4 r, Vec3 s, Texture albedo);
		static void drawRotateCube(Vec4 r, Vec3 s, Texture albedo);
		static void drawRotateCube(Vec4 r, Texture albedo);

		// Alpha blending
		static void drawBlending(Vec3 t, Vec4 r, Vec3 s, Texture albedo);
		static void drawBlending(Vec3 t, Vec3 s, Texture albedo);

		struct Utils3D
		{
			ShaderManager	 Shader;
			IDShader		 SType;
			u_ptr<VAO>		 Vao[3];
			// *-*-*-*-*-*-*-*-*-*-
			glm::mat4 Model			{ 1.0f };
			glm::mat4 View			{ 1.0f };
			glm::mat4 Projection	{ 1.0f };
		};
		static u_ptr<Utils3D> s_utils;
	};
}
