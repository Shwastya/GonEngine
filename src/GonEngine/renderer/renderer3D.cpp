#pragma once
#include "GonEngine/renderer/management/render_manager.hpp" 
#include "GonEngine/platform/OpenGL/opengl_texture.hpp" 
#include "GonEngine/platform/OpenGL/opengl_shader.hpp" 
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"   
#include "GonEngine/renderer/renderer3D.hpp"
#include "GonEngine/geometries/triangle.hpp" 
#include "GonEngine/geometries/quad.hpp" 
#include "GonEngine/geometries/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GonEngine/gon.hpp"

namespace Gon {
		
	u_ptr<Renderer3D::Buffer3D> Renderer3D::s_buffer{ nullptr };

		

	VBOLayout Renderer3D::getLayout()
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

	void Renderer3D::init()
	{
		s_buffer = make_u_ptr<Buffer3D>();
		
		// Al iniciar Renderer3D
		// Cargaremos en el VAO todas las geometrias de las que disponemos
		// Probablemente no se use todo, o no se usen normales o uvs
		// Ocuparemos más memorias pero tenemos velocidad
		// Hasta mejor idea:

		Triangle T;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*		
		s_buffer->Vao[TRIANGLE] = VAO::create(1);

		u_ptr<VBO> vbo{ VBO::create(T.get(),  T.size()) };
		vbo->setLayout(getLayout());
		s_buffer->Vao[TRIANGLE]->takeVBO(vbo);

		u_ptr<EBO> ebo{ EBO::create(T.getIndices(), T.nIndices()) };
		s_buffer->Vao[TRIANGLE]->takeEBO(ebo);

		Quad Q(1.0f);
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		s_buffer->Vao[QUAD] = VAO::create(1);

		vbo = VBO::create(Q.get(),  Q.size());
		vbo->setLayout(getLayout());
		s_buffer->Vao[QUAD]->takeVBO(vbo);

		ebo = EBO::create(Q.getIndices(), Q.nIndices());
		s_buffer->Vao[QUAD]->takeEBO(ebo);

		Cube C(1.0f);
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		s_buffer->Vao[CUBE] = VAO::create(1);

		vbo = VBO::create(C.get(),  C.size());
		vbo->setLayout(getLayout());
		s_buffer->Vao[CUBE]->takeVBO(vbo);

		ebo = EBO::create(C.getIndices(), C.nIndices());
		s_buffer->Vao[CUBE]->takeEBO(ebo);
	}

	void Renderer3D::reset()
	{
		s_buffer.reset();		
	}

	void Renderer3D::beginScene()
	{
	}

	void Renderer3D::beginScene(const glm::mat4& view, const glm::mat4& projection)
	{
		_view = view;
		_proj  = projection;
	}

	void Renderer3D::TRSsubmit()
	{
		_shader[_current]->bind();
		_shader[_current]->uniform("uModel", _model);
		_shader[_current]->uniform("uView",  _view);
		_shader[_current]->uniform("uProj",  _proj);	
		_model = glm::mat4(1.0f);
	}
	
	void Renderer3D::endScene()
	{
		_shader[_current]->unbind();
	}

	void Renderer3D::draw3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader				
		_model = glm::translate(_model, t);
		_model = glm::rotate   (_model, glm::radians(r.x), { r.y, r.z, r.w });
		_model = glm::scale    (_model, s);

		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}
	void Renderer3D::draw3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader	
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale (_model, s); 
		
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::draw3D(const Obj obj3D, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader	
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}
	void Renderer3D::draw3D(const Obj obj3D, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader	
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::drawRotate3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::translate(_model, t);
		_model = glm::rotate   (_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale    (_model, s); 
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::drawRotate3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale (_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::drawRotate3D(const Obj obj3D, Vec4 r, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		s_buffer->Vao[obj3D]->unbind();
	}
	
	// Alpha
	void Renderer3D::drawBlending(Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::translate(_model, t);
		_model = glm::rotate   (_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale	   (_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[QUAD]->bind();
		RenderCall::Draw(s_buffer->Vao[QUAD].get());
		s_buffer->Vao[QUAD]->unbind();
	}
	void Renderer3D::drawBlending(Vec3 t, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::translate(_model, t);
		_model = glm::scale	   (_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[QUAD]->bind();
		RenderCall::Draw(s_buffer->Vao[QUAD].get());
		s_buffer->Vao[QUAD]->unbind();
	}


	void Renderer3D::drawPolygon3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader				
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, glm::radians(r.x), { r.y, r.z, r.w });
		_model = glm::scale(_model, s);

		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}
	void Renderer3D::drawPolygon3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader	
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);

		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::drawPolygon3D(const Obj obj3D, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader	
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}
	void Renderer3D::drawPolygon3D(const Obj obj3D, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader	
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}


	void Renderer3D::drawRotatePolygon3D(const Obj obj3D, Vec3 t, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::drawRotatePolygon3D(const Obj obj3D, Vec4 r, Vec3 s, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);

		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::drawRotatePolygon3D(const Obj obj3D, Vec4 r, Texture albedo, Color colormask)
	{
		_current = BasicText;
		// Model Transforms an set current Shader		
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colormask);

		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_buffer->Vao[obj3D]->bind();
		RenderCall::linePolygonMode(true);
		RenderCall::Draw(s_buffer->Vao[obj3D].get());
		RenderCall::linePolygonMode(false);
		s_buffer->Vao[obj3D]->unbind();
	}

	void Renderer3D::setAlbedo(Texture albedo, Color colorMask)
	{
		_shader[_current]->uniform("uTexture", 0);
		_shader[_current]->uniform("uTextScale", albedo->getTilingScale());
		_shader[_current]->uniform("uColorMask", colorMask);
	}	
}

