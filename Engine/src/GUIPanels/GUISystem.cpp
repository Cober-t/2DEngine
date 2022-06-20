#pragma once
#include <GUISystem.h>

namespace Cober {

	GUISystem::GUISystem() {

	}

	void GUISystem::Init() {

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Style
		{
			ImGuiStyle* style = &ImGui::GetStyle();
			auto& colors = ImGui::GetStyle().Colors;

			colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.000f);
			colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 0.000f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.5f, 0.5f, 0.5f, 0.5f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.5f, 0.5, 0.5f, 0.4f);
			colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
			colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
			colors[ImGuiCol_SeparatorHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
			colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
			//colors[ImGuiCol_DockingPreview] = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
			//colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

			style->ChildRounding = 4.0f;
			style->FrameBorderSize = 1.0f;
			style->FrameRounding = 2.0f;
			style->GrabMinSize = 7.0f;
			style->PopupRounding = 2.0f;
			style->ScrollbarRounding = 12.0f;
			style->ScrollbarSize = 13.0f;
			style->TabBorderSize = 1.0f;
			style->TabRounding = 0.0f;
			style->WindowRounding = 20.0f;
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.07f, 0.07f, 0.07f, 1.0f };
		}

		Engine& engine = Engine::Get();
		SDL_Window* window = static_cast<SDL_Window*>(engine.GetWindow().GetNativeWindow());
		SDL_Renderer* renderer= static_cast<SDL_Renderer*>(engine.GetWindow().GetRenderer());
		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);
	}

	GUISystem::~GUISystem() {

		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void GUISystem::Begin() {

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void GUISystem::Update() {

		{
			ImGui::Begin("Another Window");
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				Engine::Get().CloseEngine();

			//Engine& engine = Engine::Get();
			//ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			//glm::vec2 m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			//uint32_t texture = engine.GetWindow().ScreenTexture();
			//ImGui::Image(reinterpret_cast<void*>(texture), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			
			ImGui::End();
		}
	}

	void GUISystem::End() {
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	}

	void GUISystem::OnEvent(SDL_Event& event) {

	}
}