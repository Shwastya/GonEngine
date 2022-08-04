#include "EditorLayer.hpp"

constexpr char* k_albedo_ore	= ("../assets/textures/Rock_Ore_001_SD/Rock_Ore_001_COLOR.jpg");
constexpr char* k_albedo_alien  = ("../assets/textures/Alien-muscle/Alien_Muscle_001_COLOR.jpg");
constexpr char* k_blending		= ("../assets/textures/tree.png");

namespace Gon
{
	EditorLayer::EditorLayer(const NodeType ntype, const std::string& name)
		: Layer(ntype, name),
		m_cameraMan(std::make_unique<CameraMan>
		(
			CamMode::Persp, 
			Gon_window_width / Gon_window_height,
			k_orthoData, k_perspData
		))//,
		//m_quadColor(0.3f)
	{
		m_texture[0] = Texture2D::create(k_albedo_ore, Texture2D::Format::RGB);
		m_texture[1] = Texture2D::create(k_albedo_alien, Texture2D::Format::RGB);
		m_texture[2] = Texture2D::create(k_blending, Texture2D::Format::RGBA);
	}

	EditorLayer::~EditorLayer()
	{
		Renderer3D::reset(); // solo para asegurarse y evitar leaks
	}

	void EditorLayer::onJoin()
	{
		Renderer3D::init();
	}
	void EditorLayer::onQuit()
	{
		Renderer3D::reset();
	}
	void EditorLayer::onEvent(Event& e)
	{
		m_cameraMan->onEvent(e);		
	}
	void EditorLayer::onUpdate(const DeltaTime dt)
	{
		m_cameraMan->handler()->onUpdate(dt);
		
		RenderCall::setClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		RenderCall::clear();

		Renderer3D::beginScene(m_cameraMan->View(), m_cameraMan->Projection());
		{
			Renderer3D::drawQuad({ 0.0f, -0.35f, 0.0f }, { -55.0f, 1.0f, 0.0f, 0.0f }, glm::vec3{ 1.8f }, m_texture[0].get());
			Renderer3D::drawRotateCube({-0.35f, 0.3f, -0.3f}, { 90.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.35f }, m_texture[1].get());
			Renderer3D::drawBlending({ 0.6f, 0.0f, 0.0f }, glm::vec3{ 0.5f }, m_texture[2].get());
		}		
		Renderer3D::endScene();
	}
	void EditorLayer::onRender()
	{
		/*ImGui::Begin("Set quad color");
		ImGui::ColorEdit3("Quad color", glm::value_ptr(m_quadColor));
		ImGui::End();*/
	}
}