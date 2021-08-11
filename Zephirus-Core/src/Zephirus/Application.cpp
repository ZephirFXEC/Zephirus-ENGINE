#include "zphpch.h"
#include "Application.h"

#include "Zephirus/Events/ApplicationEvent.h"
#include "Zephirus/Log.h"

namespace ZPH {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}
}