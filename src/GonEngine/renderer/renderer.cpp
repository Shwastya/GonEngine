#include "GonEngine/platform/OpenGL/opengl_texture_cube_map.hpp"
#include "GonEngine/renderer/management/render_manager.hpp" 
#include "GonEngine/renderer/cameras/camera_orthographic.hpp"
#include "GonEngine/renderer/cameras/camera_perspective.hpp"
#include "GonEngine/platform/OpenGL/opengl_texture.hpp" 
#include "GonEngine/platform/OpenGL/opengl_shader.hpp" 
#include "GonEngine/geometries/triangle.hpp" 
#include "GonEngine/renderer/renderer.hpp"
#include "GonEngine/geometries/quad.hpp" 
#include "GonEngine/geometries/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/gon.hpp"
#include <glad/glad.h>

#include "GonEngine/renderer/management/shader_manager.hpp"
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"

#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

namespace Gon
{
	struct RendererStorage
	{
		ShaderManager	 Shader;
		IDShader		 CurrentShader
		{
			IDShader::BasicText
		};
		u_ptr<VAO>		 Vao[4];

		glm::mat4 Model{ 1.0f };
		glm::mat4 View{ 1.0f };
		glm::mat4 Proj{ 1.0f };
	};
	static u_ptr<RendererStorage> s_storage;

	void Renderer::init(const bool cullface, const bool depthtest, const bool alphablending)
	{
		
		RenderMan::init(cullface, depthtest, alphablending);
		s_storage = make_u_ptr<RendererStorage>();
		Renderer::init3D();
	}
	void Renderer::reset()
	{		
		Renderer::reset3D();
		s_storage.reset();
		RenderMan::reset();	
	}
	void Renderer::setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
	{
		RenderMan::setViewPort(x, y, width, height);
	}
	void Renderer::onWindowResize(const uint32_t width, const uint32_t height)
	{
		RenderMan::setViewPort(0, 0, width, height);
	}


	VBOLayout Renderer::getLayout()
	{
		return VBOLayout
		({
			{DataType::Float3, "aPos"},
			{DataType::Float2, "aUvs"},
			{DataType::Float3, "aNormal"},
			{DataType::Float3, "aTang"},
			{DataType::Float3, "aBitang"}
		});
	}

	void Renderer::init3D()
	{

		Triangle T;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*		
		VAObj[TRIANGLE] = VAO::create(1);

		u_ptr<VBO> vbo{ VBO::create(T.get(),  T.size()) };
		vbo->setLayout(getLayout());
		VAObj[TRIANGLE]->takeVBO(vbo);

		u_ptr<EBO> ebo{ EBO::create(T.getIndices(), T.nIndices()) };
		VAObj[TRIANGLE]->takeEBO(ebo);

		Quad Q(1.0f);
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		VAObj[QUAD] = VAO::create(1);

		vbo = VBO::create(Q.get(), Q.size());
		vbo->setLayout(getLayout());
		VAObj[QUAD]->takeVBO(vbo);

		ebo = EBO::create(Q.getIndices(), Q.nIndices());
		VAObj[QUAD]->takeEBO(ebo);

		Cube C(1.0f);
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		VAObj[CUBE] = VAO::create(1);

		vbo = VBO::create(C.get(), C.size());
		vbo->setLayout(getLayout());
		VAObj[CUBE]->takeVBO(vbo);

		ebo = EBO::create(C.getIndices(), C.nIndices());
		VAObj[CUBE]->takeEBO(ebo);

		// SkyBox
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	

		const float half = 20.0f / 2.0f;
		float skyboxVertices[] = {
			// positions          
			-half,  half, -half,
			-half, -half, -half,
			 half, -half, -half,
			 half, -half, -half,
			 half,  half, -half,
			-half,  half, -half,

			-half, -half,  half,
			-half, -half, -half,
			-half,  half, -half,
			-half,  half, -half,
			-half,  half,  half,
			-half, -half,  half,

			 half, -half, -half,
			 half, -half,  half,
			 half,  half,  half,
			 half,  half,  half,
			 half,  half, -half,
			 half, -half, -half,

			-half, -half,  half,
			-half,  half,  half,
			 half,  half,  half,
			 half,  half,  half,
			 half, -half,  half,
			-half, -half,  half,

			-half,  half, -half,
			 half,  half, -half,
			 half,  half,  half,
			 half,  half,  half,
			-half,  half,  half,
			-half,  half, -half,

			-half, -half, -half,
			-half, -half,  half,
			 half, -half, -half,
			 half, -half, -half,
			-half, -half,  half,
			 half, -half,  half
		};

		VAObj[SKYBOX] = VAO::create(1);

		u_ptr<VBO> vboSky{ VBO::create(skyboxVertices, sizeof(skyboxVertices)) };
		vboSky->setLayout({{DataType::Float3, "aPos"}});
		VAObj[SKYBOX]->takeVBO(vboSky);
	}

	void Renderer::reset3D()
	{
		VAObj->reset();
	}

	void Renderer::beginScene(const glm::mat4& view, const glm::mat4& projection)
	{
		VIEW = view;
		PROJ = projection;
	}

	void Renderer::drawSkyBox(const CubeMapText* skybox)
	{		
		const glm::mat4 backupView{ VIEW };
		{
			VIEW = glm::mat4(glm::mat3(VIEW));

			SHADER[SkyBox]->uniform("uSkybox", 0);
			skybox->bind();
			SHADER[SkyBox]->bind();
			SHADER[SkyBox]->uniform("uView", VIEW);
			SHADER[SkyBox]->uniform("uProj", PROJ);

			VAObj[SKYBOX]->bind();

			RenderMan::setFalseDepthMask();
			RenderMan::Draw(36);
			RenderMan::setTrueDepthMask();
			VAObj[SKYBOX]->unbind();
		}
		VIEW = backupView;
	}

	

	void Renderer::TRSsubmit()
	{
		SHADER[current]->bind();
		SHADER[current]->uniform("uModel", MODEL);
		SHADER[current]->uniform("uView",  VIEW);
		SHADER[current]->uniform("uProj",  PROJ);
		MODEL = glm::mat4(1.0f);
	}

	void Renderer::endScene()
	{
		SHADER[current]->unbind();
	}

	void Renderer::draw3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader				
		MODEL = glm::translate(MODEL, t);
		MODEL = glm::rotate(MODEL, glm::radians(r.x), { r.y, r.z, r.w });
		MODEL = glm::scale(MODEL, s);

		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();
	}
	void Renderer::draw3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader	
		MODEL = glm::rotate(MODEL, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);

		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();
	}

	void Renderer::draw3D(const Geo Geo3D, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader	
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();
	}
	void Renderer::draw3D(const Geo Geo3D, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader	
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();
	}

	void Renderer::drawRotate3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::translate(MODEL, t);
		MODEL = glm::rotate(MODEL, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();		
	}

	void Renderer::drawRotate3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::rotate(MODEL, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);

		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();
	}

	void Renderer::drawRotate3D(const Geo Geo3D, VEC4 r, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::rotate(MODEL, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);

		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::Draw(VAObj[Geo3D].get());
		VAObj[Geo3D]->unbind();
	}

	// Alpha
	void Renderer::drawBlending(VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::translate(MODEL, t);
		MODEL = glm::rotate(MODEL, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[QUAD]->bind();
		RenderMan::Draw(VAObj[QUAD].get());
		VAObj[QUAD]->unbind();
	}
	void Renderer::drawBlending(VEC3 t, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::translate(MODEL, t);
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[QUAD]->bind();
		RenderMan::Draw(VAObj[QUAD].get());
		VAObj[QUAD]->unbind();
	}

	

	void Renderer::drawPolygon3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader				
		MODEL = glm::translate(MODEL, t);
		MODEL = glm::rotate(MODEL, glm::radians(r.x), { r.y, r.z, r.w });
		MODEL = glm::scale(MODEL, s);

		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}
	void Renderer::drawPolygon3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader	
		MODEL = glm::rotate(MODEL, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);

		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms

		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}

	void Renderer::drawPolygon3D(const Geo Geo3D, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader	
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}
	void Renderer::drawPolygon3D(const Geo Geo3D, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader	
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}


	void Renderer::drawRotatePolygon3D(const Geo Geo3D, VEC3 t, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::translate(MODEL, t);
		MODEL = glm::rotate(MODEL, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}

	void Renderer::drawRotatePolygon3D(const Geo Geo3D, VEC4 r, VEC3 s, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::rotate(MODEL, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		MODEL = glm::scale(MODEL, s);
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);

		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}

	void Renderer::drawRotatePolygon3D(const Geo Geo3D, VEC4 r, Texture albedo, Color colormask)
	{
		current = BasicText;
		// Model Transforms an set current Shader		
		MODEL = glm::rotate(MODEL, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		SHADER[BasicText]->uniform("uTexture", 0);
		SHADER[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		SHADER[BasicText]->uniform("uColorMask", colormask);

		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		VAObj[Geo3D]->bind();
		RenderMan::linePolygonMode(true);
		RenderMan::Draw(VAObj[Geo3D].get());
		RenderMan::linePolygonMode(false);
		VAObj[Geo3D]->unbind();
	}
}