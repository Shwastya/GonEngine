#include "EditorLayer.hpp"

constexpr char* k_albedo = ("../assets/textures/Rock_Ore_001_SD/Rock_Ore_001_COLOR.jpg");
constexpr char* k_blending = ("../assets/textures/tree.png");

constexpr char* k_basicShader_1 = ("../assets/shaders/GLSL/basic1.glsl");
constexpr char* k_basicShader_2 = ("../assets/shaders/GLSL/basic2.glsl");


namespace Gon
{
	EditorLayer::EditorLayer(const GOType ntype, const std::string& name)
		: GameObject(ntype, name),

		m_vao{ VAO::create(2) }, m_vao2{ VAO::create(1) },
		m_shader{ Shader::create(k_basicShader_1) },
		m_shader2{ Shader::create(k_basicShader_2) },
		m_texture{Texture2D::create(k_albedo, Texture2D::Format::RGB)},
		m_alphaTexture{ Texture2D::create(k_blending, Texture2D::Format::RGBA) },
		m_quadColor(0.3f)
	{
		m_render.InitConfiguration(true, false, true);

		/**********************************************************/
		Triangle triangle;

		u_ptr<VBO> vbo{ VBO::create(triangle.get(),  triangle.size()) };
		vbo->setLayout
		({
			{ DataType::Float3, "aPos" },
			{ DataType::Float2, "aUvs" },
			{ DataType::Float3, "aNormal" },
			{ DataType::Float3, "aTang" },
			{ DataType::Float3, "aBitang" }
		});
		m_vao->takeVBO(vbo);

		float vertexColor[3 * 3]
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
		u_ptr<VBO> vbo2{ VBO::create(vertexColor, sizeof(vertexColor)) };
		vbo2->setLayout({ {DataType::Float3, "aColor"} });
		m_vao->takeVBO(vbo2);


		u_ptr<EBO> ebo{ EBO::create(triangle.getIndices(), triangle.nIndices()) };
		m_vao->takeEBO(ebo);


		/**********************************************************/
		Quad quad(1.5f);

		u_ptr<VBO> vbo3{ VBO::create(quad.get(),  quad.size()) };
		vbo3->setLayout
		({
			{DataType::Float3, "aPos"},
			{DataType::Float2, "aUvs"},
			{DataType::Float3, "aNormal"},
			{DataType::Float3, "aTang"},
			{DataType::Float3, "aBitang"}
		});
		m_vao2->takeVBO(vbo3);

		u_ptr<EBO> ebo2{ EBO::create(quad.getIndices(), quad.nIndices()) };
		m_vao2->takeEBO(ebo2);		
	}

	void EditorLayer::onJoin()
	{
	}
	void EditorLayer::onQuit()
	{
	}
	void EditorLayer::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::KeyPressed)
		{
			OnKeyPressed& _e = dynamic_cast<OnKeyPressed&>(e);

			if (_e.getKeyCode() == GON_KEY_C)
			{
				if (m_cameraMan.getCamMode() != CamMode::Ortho)
					m_cameraMan.switchCam(CamMode::Ortho);
				else m_cameraMan.switchCam(CamMode::Persp);
			}
			if (_e.getKeyCode() == GON_KEY_R)
			{
				m_cameraMan.setRotation(45.0f);
			}
		}
	}
	void EditorLayer::onUpdate(const DeltaTime dt)
	{
		m_render.begin(m_cameraMan.getCam());		
		
		m_shader2->uniform("uTexture", 0);
		m_texture->bind();
		m_render.submit(m_vao2.get(), m_shader2.get());

		m_shader2->uniform("uTexture", 0);
		m_alphaTexture->bind();
		glm::mat4 model1{ 1.0f };
		model1 = glm::translate(model1, glm::vec3(0.4f, -0.8f, 0.0f));
		model1 = glm::scale(model1, glm::vec3(0.4f));		
		m_render.submit(m_vao2.get(), m_shader2.get(), model1);		

		const float dance = static_cast<float>(glm::abs(glm::cos(GonEngine::getTime())));
		glm::mat4 model{ 1.0f };
		model = glm::translate	(model, glm::vec3(0.0f, dance, 0.0f));
		model = glm::rotate		(model, (float)GonEngine::getTime() * glm::radians(90.0f ) , glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale		(model, glm::vec3(0.4f));

		m_render.submit(m_vao.get(), m_shader.get(), model);		
	}
	void EditorLayer::onRender()
	{
		ImGui::Begin("Set quad color");
		ImGui::ColorEdit3("Quad color", glm::value_ptr(m_quadColor));
		ImGui::End();
	}
}