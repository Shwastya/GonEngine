#pragma once
#include "GonEngine/renderer/management/shader_manager.hpp" 
#include "GonEngine/renderer/renderer.hpp"

namespace Gon {

	#define _current s_buffer->SType
	#define _shader	 s_buffer->Shader

	#define Vec3	const glm::vec3&
	#define Vec4	const glm::vec4&
	#define Texture	const Texture2D*
	#define Color	const glm::vec4&

	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class	ShaderManager;
	struct	VBOLayout;
	class	Texture2D;
	class	Shader;
	struct	VAO;
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	
	
	class Renderer3D {

	public:
	enum  Obj
	{
		TRIANGLE = 0,
		QUAD, 
		CUBE,
		BLEENDIG = QUAD
	};

	public:

		Renderer3D()  = delete;
		~Renderer3D() = delete;

		static VBOLayout getLayout();
		static void init();
		static void reset();

		static void beginScene();
		static void beginScene(const glm::mat4& view, const glm::mat4& projection);
		static void TRSsubmit();
		//static void TRSsubmit();
		static void endScene();			

		// Quad
		static void draw3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void draw3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void draw3D(const Obj obj3D, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void draw3D(const Obj obj3D, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotate3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotate3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });	
		static void drawRotate3D(const Obj obj3D, Vec4 r, Texture albedo, Color colormask = glm::vec4{ 1.0f });	
		
		static void drawPolygon3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Obj obj3D, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawPolygon3D(const Obj obj3D, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		static void drawRotatePolygon3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotatePolygon3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawRotatePolygon3D(const Obj obj3D, Vec4 r, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		// Alpha blending
		static void drawBlending(Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });
		static void drawBlending(Vec3 t, Vec3 s, Texture albedo, Color colormask = glm::vec4{ 1.0f });

		struct Buffer3D
		{
			ShaderManager	 Shader;
			IDShader		 SType;
			u_ptr<VAO>		 Vao[3];
		};
		static u_ptr<Buffer3D> s_buffer;

	private:

		static void setAlbedo(Texture albedo, Color colorMask);
	};
}
