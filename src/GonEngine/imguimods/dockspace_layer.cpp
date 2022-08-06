#include "GonEngine/imguimods/dockspace_layer.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include "GonEngine/gon.hpp"
#include <imgui.h>

namespace Gon {

	ImGuiDockSpace::ImGuiDockSpace(const NodeType ntype, const std::string& name)
		: Node(ntype, name)
	{
		GON_TRACE("[CREATED] Layer: (Type: {0}) > (Name: {1}) > (Id: {2})", NodeTypeToString(m_nodeType), m_name, m_id);
	}

	ImGuiDockSpace::~ImGuiDockSpace()
	{
		GON_TRACE("[DESTROYED] ImGui DockSpace configuration.");
	}

	void ImGuiDockSpace::onJoin()
	{
		// future configs
	}

	void ImGuiDockSpace::onQuit()
	{
        // future configs
	}

	void ImGuiDockSpace::Begin()
	{
        // ImGui DockSpace
        // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

        // If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
        // In this specific demo, we are not using DockSpaceOverViewport() because:
        // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
        // - we allow the host window to have padding (when opt_padding == true)
        // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
        // TL;DR; this demo is more complicated than what you would normally use.
        // If we removed all the options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        //     }

        //const static bool opt_fullscreen = true;

        static bool opt_padding{ false };
        static ImGuiDockNodeFlags dockspace_flags{ ImGuiDockNodeFlags_None };
        static bool dockspaceOpen{ true };


        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags{ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking };
       
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;        

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding) ImGui::PopStyleVar();
        
        ImGui::PopStyleVar(2);

        // Submit the DockSpace
        const ImGuiIO& io{ ImGui::GetIO() };
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }        

        

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit")) GonEngine::getGon().closeGonEngine();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();
                if (ImGui::MenuItem(m_menu.FullscreenMenuItem))
                {
                    if (!m_menu.IsFullScreen)
                    {
                        GonEngine::getGon().getPtrWindow().enableFullScreenWindow();
                        m_menu.FullscreenMenuItem = "Windowed mode";
                        m_menu.IsFullScreen = true;
                    }
                    else
                    {
                        GonEngine::getGon().getPtrWindow().enableWindowedWindow();
                        m_menu.FullscreenMenuItem = "Fullscreen mode";
                        m_menu.IsFullScreen = false;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        
	}

	void ImGuiDockSpace::End()
	{        
        ImGui::End();
	}
}