#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include "GonEngine/engine/nodes/n_imgui.hpp"
#include "GonEngine/engine/gon.hpp"
#include "glm/vec2.hpp"
namespace gon 
{
	//ImGuiLayer::ImGuiLayer(const NodeType ntype = NodeType::Project) 
	//	: Node(ntype) {}
#if defined (_NODE_NAMETEST) && (_DEBUG)	
	ImGuiLayer::ImGuiLayer(const NodeType ntype = NodeType::Project, const std::string& name = "test")
		: Node(ntype, name)
	{}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::onJoin()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		
	}
	void ImGuiLayer::onQuit()
	{
		
	}
	void ImGuiLayer::begin()
	{
		
	}
	void ImGuiLayer::end()
	{
	}
	void ImGuiLayer::setGonColorProfile()
	{
	}
#endif
}

