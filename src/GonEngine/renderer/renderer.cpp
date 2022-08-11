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
		ShaderManager	Shader;
		IDShader		CurrentShader {IDShader::BasicText};
		u_ptr<Geometry> geometry[4];

		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 View  = glm::mat4(1.0f);
		glm::mat4 Proj  = glm::mat4(1.0f);
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

	void Renderer::init3D()
	{
		s_storage->geometry[Geometry::QUAD]   = Geometry::create(Geometry::QUAD, 1.0f);
		s_storage->geometry[Geometry::CUBE]   = Geometry::create(Geometry::CUBE, 1.0f);
		s_storage->geometry[Geometry::SKYBOX] = Geometry::create(Geometry::SKYBOX);
	}

	void Renderer::reset3D()
	{
		// TODO: administrar memoria
	}

	void Renderer::beginScene(const glm::mat4& view, const glm::mat4& projection)
	{
		s_storage->View = view;
		s_storage->Proj = projection;
	}

	void Renderer::drawSkyBox(const CubeMapText* skybox)
	{			
		// 1		
		s_storage->Shader[SkyBox]->bind();
		s_storage->Shader[SkyBox]->uniform("uView", glm::mat4(glm::mat3(s_storage->View)));
		s_storage->Shader[SkyBox]->uniform("uProj", s_storage->Proj);
			
		// 2
		s_storage->Shader[SkyBox]->uniform("uSkybox", 0);
		skybox->bind();

		// 3
		s_storage->geometry[Geometry::SKYBOX]->draw();		
	}	

	void Renderer::TRSsubmit()
	{
		s_storage->Shader[current]->bind();
		s_storage->Shader[current]->uniform("uModel", s_storage->Model);
		s_storage->Shader[current]->uniform("uView",  s_storage->View);
		s_storage->Shader[current]->uniform("uProj",  s_storage->Proj);
		s_storage->Model = glm::mat4(1.0f);
		
	}

	void Renderer::endScene()
	{
		s_storage->Shader[current]->unbind();
	}

	void Renderer::draw3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{
		// 1
		s_storage->Model = glm::translate(s_storage->Model, t);
		s_storage->Model = glm::rotate(s_storage->Model, glm::radians(r.x), { r.y, r.z, r.w });
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2		
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();

		// 3
		s_storage->geometry[Geo3D]->draw();
	}
	void Renderer::draw3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{
		// 1
		s_storage->Model = glm::rotate(s_storage->Model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geo3D]->draw();
	}

	void Renderer::draw3D(const Geometry::Type Geo3D, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1	
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geo3D]->draw();
	}
	void Renderer::draw3D(const Geometry::Type Geo3D, texture2D albedo, vector4 colormask)
	{
		// 1
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geo3D]->draw();
	}

	void Renderer::drawRotate3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1
		s_storage->Model = glm::translate(s_storage->Model, t);
		s_storage->Model = glm::rotate(s_storage->Model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);		
		albedo->bind();
		
		// 3
		s_storage->geometry[Geo3D]->draw();
	}

	void Renderer::drawRotate3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1
		s_storage->Model = glm::rotate(s_storage->Model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geo3D]->draw();
	}

	void Renderer::drawRotate3D(const Geometry::Type Geo3D, vector4 r, texture2D albedo, vector4 colormask)
	{		
		// 1		
		s_storage->Model = glm::rotate(s_storage->Model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geo3D]->draw();
	}

	void Renderer::drawBlending(vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1
		s_storage->Model = glm::translate(s_storage->Model, t);
		s_storage->Model = glm::rotate(s_storage->Model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geometry::QUAD]->draw();
	}
	void Renderer::drawBlending(vector3 t, vector3 s, texture2D albedo, vector4 colormask)
	{
		// 1
		s_storage->Model = glm::translate(s_storage->Model, t);
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2				
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		s_storage->geometry[Geometry::QUAD]->draw();
	}

	

	void Renderer::drawPolygon3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{
		// 1
		s_storage->Model = glm::translate(s_storage->Model, t);
		s_storage->Model = glm::rotate(s_storage->Model, glm::radians(r.x), { r.y, r.z, r.w });
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();
		
		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}
	void Renderer::drawPolygon3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1
		s_storage->Model = glm::rotate(s_storage->Model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}

	void Renderer::drawPolygon3D(const Geometry::Type Geo3D, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}
	void Renderer::drawPolygon3D(const Geometry::Type Geo3D, texture2D albedo, vector4 colormask)
	{
		// 1
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}


	void Renderer::drawRotatePolygon3D(const Geometry::Type Geo3D, vector3 t, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{
		// 1		
		s_storage->Model = glm::translate(s_storage->Model, t);
		s_storage->Model = glm::rotate(s_storage->Model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}

	void Renderer::drawRotatePolygon3D(const Geometry::Type Geo3D, vector4 r, vector3 s, texture2D albedo, vector4 colormask)
	{		
		// 1
		s_storage->Model = glm::rotate(s_storage->Model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		s_storage->Model = glm::scale(s_storage->Model, s);
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// 3
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}

	void Renderer::drawRotatePolygon3D(const Geometry::Type Geo3D, vector4 r, texture2D albedo, vector4 colormask)
	{
		// 1		
		s_storage->Model = glm::rotate(s_storage->Model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		current = BasicText;
		TRSsubmit();

		// 2
		s_storage->Shader[BasicText]->uniform("uTexture", 0);
		s_storage->Shader[BasicText]->uniform("uTextScale", albedo->getTilingScale());
		s_storage->Shader[BasicText]->uniform("uColorMask", colormask);
		albedo->bind();
		
		// bind VAO an DRAW
		RenderMan::linePolygonMode(true);
		s_storage->geometry[Geo3D]->draw();;
		RenderMan::linePolygonMode(false);
	}
}