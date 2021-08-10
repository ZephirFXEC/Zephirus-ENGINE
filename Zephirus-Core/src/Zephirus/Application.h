#pragma once

#include "Core.h"

namespace ZPH {

	class ZPH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	
	};

	//To be defined in client
	Application* CreateApplication();
}


   