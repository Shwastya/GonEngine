#include "EditorLayer.hpp"


namespace Gon
{
	constexpr char* k_albedo_ore	{ "../assets/textures/Rock_Ore_001_SD/Rock_Ore_001_COLOR.jpg" };
	constexpr char* k_albedo_alien	{ "../assets/textures/Alien-muscle/Alien_Muscle_001_COLOR.jpg" };
	constexpr char* k_albedo_lava	{ "../assets/textures/Lava_002/Lava_002_COLOR.jpg" };
	constexpr char* k_blending		{ "../assets/textures/tree.png" };

	const std::vector<std::string>k_cubemap
	{
		{"../assets/textures/cubemaps/skybox/right.jpg"},   // +X
		{"../assets/textures/cubemaps/skybox/left.jpg"},    // -X
		{"../assets/textures/cubemaps/skybox/top.jpg"},     // +Y
		{"../assets/textures/cubemaps/skybox/bottom.jpg"},  // -Y
		{"../assets/textures/cubemaps/skybox/front.jpg"},   // +Z
		{"../assets/textures/cubemaps/skybox/back.jpg"},    // -Z
	};
	
	
	EditorLayer::EditorLayer(const NodeType ntype, const std::string& name)
		: Layer(ntype, name)			
	{
		m_texture[0] = Texture2D::create(k_albedo_ore, Texture2D::Format::RGB);
		m_texture[1] = Texture2D::create(k_albedo_alien, Texture2D::Format::RGB);
		m_texture[2] = Texture2D::create(k_blending, Texture2D::Format::RGBA);
		m_texture[3] = Texture2D::create(k_albedo_lava, Texture2D::Format::RGB);

		m_cubemapText = CubeMapText::create(k_cubemap, CubeMapText::Format::RGB);
		
	}

	EditorLayer::~EditorLayer()	{}

	void EditorLayer::onJoin()
	{
		m_viewPort = { (gonWindowWidth / 1.5f), (gonWindowHeight / 1.5f) };

		m_cameraMan = make_s_ptr<CameraMan>
		(
			CamMode::Persp,
			m_viewPort.x / m_viewPort.y,
			k_orthoData, k_perspData
		);
		m_cameraMan->disablePrimeWindowResize();

		FBProps frameBufferProps
		{
			static_cast<uint32_t>(m_viewPort.x),
			static_cast<uint32_t>(m_viewPort.y),
			{ FBTextureFormat::RGBA8 }
		};
		m_frameBuffer = FrameBuffer::create(frameBufferProps);

		//Renderer::linkCameraHandler();
	}
	void EditorLayer::onQuit()
	{
	}
	void EditorLayer::onEvent(Event& e)
	{
		m_cameraMan->onEvent(e);
	}
	void EditorLayer::onUpdate(const DeltaTime dt)
	{		
		{		
			// Camera::onUpdate
			{				
				GON_UI_TIMING("Camera::onUpdate");
				if (m_windowHovered) m_cameraMan->handler()->onUpdate(dt);
			}
			// Render Set
			{
				m_frameBuffer->bind();
				
				GON_UI_TIMING("Render setting");
				RenderMan::setClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
				RenderMan::clear();
			}
			// Render Runtime
			{				
				GON_UI_TIMING("Render runTime");				

				Renderer::beginScene(m_cameraMan->View(), m_cameraMan->Projection());				
				{
					
					Renderer::drawSkyBox(m_cubemapText.get());

					Renderer::drawRotatePolygon3D(CUBE, { 0.6f, 0.55f, -0.6f }, { 23.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.36f }, m_texture[1].get());
					Renderer::drawRotate3D(CUBE, { -0.1f, 0.2f, -0.2f }, { 90.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.2f }, m_texture[3].get());
					Renderer::draw3D(QUAD, { 0.0f, -0.35f, 0.0f }, { -55.0f, 1.0f, 0.0f, 0.0f }, glm::vec3{ 1.8f }, m_texture[0].get());
					Renderer::drawBlending({ 0.6f, 0.0f, 0.0f }, glm::vec3{ 0.5f }, m_texture[2].get());
					Renderer::drawRotate3D(CUBE, { 0.0f, -0.1f, 0.3f }, { -90.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.23f }, m_texture[3].get());
					Renderer::drawRotate3D(CUBE, { -0.4f, 0.3f, 0.3f }, { -50.0f, 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.4f }, m_texture[1].get(), { 0.5, 0.0, 1.0, 0.5 });
					Renderer::drawRotate3D(CUBE, { 0.15f, 0.3f, 0.3f }, { +32.0f, 0.5f, 0.3f, 0.7f }, glm::vec3{ 0.23f }, m_texture[1].get(), { 1.0, 1.0, 1.0, 0.5 });

					
					
				}			
				Renderer::endScene();

				m_frameBuffer->unbind();
			}
		}		
	}

	void EditorLayer::onRender()
	{
		GON_UI_TIMING("UI::onRender");
		m_dock_space.Begin();
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			{
				ImGui::Begin("Scene");

				const ImVec2 viewportUI{ ImGui::GetContentRegionAvail() };
				if (m_viewPort != *((glm::vec2*)&viewportUI))
				{
					m_frameBuffer->resize((uint32_t)viewportUI.x, (uint32_t)viewportUI.y);
					m_viewPort = { viewportUI.x, viewportUI.y };
					m_cameraMan->refreshAspectRatio(m_viewPort);
				}
				const uint64_t textureID{ m_frameBuffer->getFBOTexture() };
				ImGui::Image
				(
					reinterpret_cast<ImTextureID*>(textureID),
					ImVec2{ m_viewPort.x, m_viewPort.y }, 
					ImVec2{ 0, 1 }, ImVec2{ 1, 0 }
				);				
			}	
			m_windowFocused = ImGui::IsWindowFocused();
			m_windowHovered = ImGui::IsWindowHovered();
			ImGui::PopStyleVar();
			ImGui::End();

			
		}		
		GON_UI_TIMING_SHOW_RESULTS("EditorLayer::Timer");
		m_dock_space.End();
	}
}