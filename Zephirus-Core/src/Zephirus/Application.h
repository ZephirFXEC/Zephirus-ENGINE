#pragma once


#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Zephirus/Core/Timestep.h"

#include "Zephirus/ImGui/ImGuiLayer.h"

#include "Zephirus/Renderer/Shader.h"
#include "Zephirus/Renderer/Buffer.h"
#include "Zephirus/Renderer/VertexArray.h"
#include "Zephirus/Renderer/OrthographicCamera.h"


namespace ZPH {

	class ZPH_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		Scope<Window> m_Window;
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

   