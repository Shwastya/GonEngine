#pragma once
#include "GonEngine/renderer/management/shader_manager.hpp" 
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

	u_ptr<Renderer3D::Utils3D> Renderer3D::s_utils{ nullptr };

	enum  Geometries 
	{ 
		triangle = 0, quad, cube
	};

	

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
		s_utils = std::make_unique<Utils3D>();
		
		// Al iniciar Renderer3D
		// Cargaremos en el VAO todas las geometrias de las que disponemos
		// Probablemente no se use todo, o no se usen normales o uvs
		// Ocuparemos más memorias pero tenemos velocidad
		// Hasta mejor idea:

		
		Triangle T;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*		
		s_utils->Vao[triangle] = VAO::create(1);

		u_ptr<VBO> vbo{ VBO::create(T.get(),  T.size()) };
		vbo->setLayout(getLayout());
		s_utils->Vao[triangle]->takeVBO(vbo);

		u_ptr<EBO> ebo{ EBO::create(T.getIndices(), T.nIndices()) };
		s_utils->Vao[triangle]->takeEBO(ebo);

		Quad Q(1.0f);
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		s_utils->Vao[quad] = VAO::create(1);

		vbo = VBO::create(Q.get(),  Q.size());
		vbo->setLayout(getLayout());
		s_utils->Vao[quad]->takeVBO(vbo);

		ebo = EBO::create(Q.getIndices(), Q.nIndices());
		s_utils->Vao[quad]->takeEBO(ebo);

		Cube C(1.0f);
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		s_utils->Vao[cube] = VAO::create(1);

		vbo = VBO::create(C.get(),  C.size());
		vbo->setLayout(getLayout());
		s_utils->Vao[cube]->takeVBO(vbo);

		ebo = EBO::create(C.getIndices(), C.nIndices());
		s_utils->Vao[cube]->takeEBO(ebo);

		vbo.reset(); ebo.reset();
		

	}
	void Renderer3D::reset()
	{
		s_utils.reset();		
		s_utils = nullptr;
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
	}
	
	void Renderer3D::endScene()
	{
		_shader[_current]->unbind();
	}

	// Quad
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void Renderer3D::drawQuad(Vec3 t, Vec4 r, Vec3 s, Texture albedo)
	{	
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}
	void Renderer3D::drawQuad(Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader	
		_model = glm::mat4(1.0f);
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}

	void Renderer3D::drawQuad(Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader	
		_model = glm::mat4(1.0f);
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}
	void Renderer3D::drawQuad(Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader	
		_model = glm::mat4(1.0f);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}

	void Renderer3D::drawRotateQuad(Vec3 t, Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}

	void Renderer3D::drawRotateQuad(Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}

	void Renderer3D::drawRotateQuad(Vec4 r, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[quad].get());
		s_utils->Vao[quad]->unbind();
	}

	// Cube
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void Renderer3D::drawCube(Vec3 t, Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}
	void Renderer3D::drawCube(Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader	
		_model = glm::mat4(1.0f);
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}

	void Renderer3D::drawCube(Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader	
		_model = glm::mat4(1.0f);
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}
	void Renderer3D::drawCube(Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader	
		_model = glm::mat4(1.0f);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}

	void Renderer3D::drawRotateCube(Vec3 t, Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}

	void Renderer3D::drawRotateCube(Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}

	void Renderer3D::drawRotateCube(Vec4 r, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::rotate(_model, static_cast<float>(GonEngine::getTime()) * glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[cube]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[cube]->unbind();
	}

	// Alpha
	void Renderer3D::drawBlending(Vec3 t, Vec4 r, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, t);
		_model = glm::rotate(_model, glm::radians(r.x), glm::vec3(r.y, r.z, r.w));
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[quad]->unbind();
	}
	void Renderer3D::drawBlending(Vec3 t, Vec3 s, Texture albedo)
	{
		_current = Basic;
		// Model Transforms an set current Shader		
		_model = glm::mat4(1.0f);
		_model = glm::translate(_model, t);
		_model = glm::scale(_model, s);
		_shader[_current]->uniform("uTexture", 0);
		// bind albedo and submit TRS Uniforms
		albedo->bind();
		TRSsubmit();
		// bind VAO an DRAW
		s_utils->Vao[quad]->bind();
		RenderCall::Draw(s_utils->Vao[cube].get());
		s_utils->Vao[quad]->unbind();
	}
}
