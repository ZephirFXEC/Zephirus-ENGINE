#pragma once

#ifdef ZPH_PLATFORM_WINDOWS

extern ZPH::Application* ZPH::CreateApplication();

int main(int argc, char** argv)
{

	ZPH::Log::Init();

	ZPH_CORE_WARN("Initializd Log!");
	auto app = ZPH::CreateApplication();
	app->Run();
	delete app;
}

#endif