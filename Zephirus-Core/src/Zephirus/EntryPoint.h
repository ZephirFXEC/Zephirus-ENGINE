#pragma once

#ifdef ZPH_PLATFORM_WINDOWS

extern ZPH::Application* ZPH::CreateApplication();

int main(int argc, char** argv)
{
	auto app = ZPH::CreateApplication();
	app->Run();
	delete app;
}

#endif