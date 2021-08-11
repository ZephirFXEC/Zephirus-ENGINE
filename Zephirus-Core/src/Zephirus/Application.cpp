#include "zphpch.h"
#include "Application.h"

#include "Zephirus/Events/ApplicationEvent.h"
#include "Zephirus/Log.h"

namespace ZPH {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		WindowResizeEvent e(1280, 720);
		ZPH_TRACE(e);
		while (true);
	}
}