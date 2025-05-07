#pragma once

#include "Core.h"

#include "Window.h"
#include "Wizar/LayerStack.h"
#include "Wizar/Events/Event.h"
#include "Wizar/Events/ApplicationEvent.h"

#include "Wizar/Core/Timestep.h"

#include "Wizar/ImGui/ImGuiLayer.h"

namespace Wizar {

	class WIZAR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}