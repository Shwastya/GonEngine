#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "GonEngine/imguimods/imgui_config_layer.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"
#include <GLFW/glfw3.h>

namespace gon 
{
	
	
	
	ImguiLayerSet::~ImguiLayerSet()
	{
		onQuit();
	}
	void ImguiLayerSet::onJoin()
	{
		

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO(); //(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		// Setup Platform/Renderer backends
		GonEngine& gonEngine = GonEngine::getGon();		
		GLFWwindow* window = static_cast<GLFWwindow*>(gonEngine.getPtrWindow().getWindow());
		
		//if (window == NULL) GON_ASSERT("Windows is NULL", window);		

		//glfwMakeContextCurrent(window);
		//glfwSwapInterval(1); // Enable vsync
		ImGui_ImplGlfw_InitForOpenGL(window, true);		
		ImGui_ImplOpenGL3_Init("#version 410");

		GON_TRACE("[CREATED] ImGui CFG layer.");
	}


	void ImguiLayerSet::onQuit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();	
		GON_TRACE("[DESTROYED] ImGui CFG context.");
	}

	// Header
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void ImguiLayerSet::ImguiBegin()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();	
	}
	// Render
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void ImguiLayerSet::OnRender()
	{
		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	// Footer
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	void ImguiLayerSet::ImguiEnd()
	{
		ImGuiIO& io = ImGui::GetIO();
		GonEngine& gonEngine = GonEngine::getGon();
		 
		io.DisplaySize = ImVec2
		{
			static_cast<float>(gonEngine.getPtrWindow().width()),
			static_cast<float>(gonEngine.getPtrWindow().height())
		};
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

	}
	void ImguiLayerSet::GonColors()
	{
	}

}

