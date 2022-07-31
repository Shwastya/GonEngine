#include "EditorLayer.hpp"

constexpr char* k_albedo = ("../assets/textures/Rock_Ore_001_SD/Rock_Ore_001_COLOR.jpg");
constexpr char* k_blending = ("../assets/textures/tree.png");

namespace Gon
{
	EditorLayer::EditorLayer(const GOType ntype, const std::string& name)
		: GameObject(ntype, name),

		m_vao{ VAO::create(2) }, m_vao2{ VAO::create(1) },
		m_texture{ Texture2D::create(k_albedo, Texture2D::Format::RGB) },
		m_alphaTexture{ Texture2D::create(k_blending, Texture2D::Format::RGBA) },
		m_cameraMan(std::make_shared<CameraMan>(CamMode::Persp, Gon_window_width / Gon_window_height)),
		m_quadColor(0.3f)
	{
		m_render.InitConfiguration(true, false, true);
		
		/**********************************************************/
		Cube cube(1.0f);

		u_ptr<VBO> vbo{ VBO::create(cube.get(),  cube.size()) };
		vbo->setLayout
		({
			{ DataType::Float3, "aPos" },
			{ DataType::Float2, "aUvs" },
			{ DataType::Float3, "aNormal" },
			{ DataType::Float3, "aTang" },
			{ DataType::Float3, "aBitang" }
		});
		m_vao->takeVBO(vbo);

		// rainbow color vbo
		u_ptr<VBO> vbo2{ VBO::create(cube.getRainbowColor(), cube.size())};
		vbo2->setLayout({ {DataType::Float3, "aColor"} });
		m_vao->takeVBO(vbo2);

		u_ptr<EBO> ebo{ EBO::create(cube.getIndices(), cube.nIndices()) };
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

		m_render.shareCam(m_cameraMan);
	}

	void EditorLayer::onJoin()
	{
	}
	void EditorLayer::onQuit()
	{
	}
	void EditorLayer::onEvent(Event& e)
	{
		m_cameraMan->handler()->onEvent(e);

		if (e.getEventType() == EventType::KeyPressed)
		{
			OnKeyPressed& _e = dynamic_cast<OnKeyPressed&>(e);

			if (_e.getKeyCode() == GON_KEY_C)
			{
				if (m_cameraMan->getCamMode() != CamMode::Ortho)
					m_cameraMan->switchCam(CamMode::Ortho);
				else m_cameraMan->switchCam(CamMode::Persp);
			}
		}
	}
	void EditorLayer::onUpdate(const DeltaTime dt)
	{
		
		m_cameraMan->handler()->onUpdate(dt);

		m_render.begin();		
		
		m_shader[Basic2]->uniform("uTexture", 0);
		m_texture->bind();
		m_render.submit(m_vao2.get(), m_shader[Basic2]);

		m_shader[Basic2]->uniform("uTexture", 0);
		m_alphaTexture->bind();
		glm::mat4 model1{ 1.0f };
		model1 = glm::translate(model1, glm::vec3(0.6f, -0.8f, 0.0f));
		model1 = glm::scale(model1, glm::vec3(0.4f));		
		m_render.submit(m_vao2.get(), m_shader[Basic2], model1);

		const float dance = static_cast<float>(glm::abs(glm::cos(GonEngine::getTime()))) - 0.5f;
		glm::mat4 model{ 1.0f };
		model = glm::translate	(model, glm::vec3(0.0f, dance , 0.0f));
		model = glm::rotate		(model, (float)GonEngine::getTime() * glm::radians(90.0f ) , glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale		(model, glm::vec3(0.4f));

		m_render.submit(m_vao.get(), m_shader[Basic1], model);
	}
	void EditorLayer::onRender()
	{
		ImGui::Begin("Set quad color");
		ImGui::ColorEdit3("Quad color", glm::value_ptr(m_quadColor));
		ImGui::End();
	}
}