#include <Zephirus.h>

class Sandbox : public ZPH::Application {

public:
	Sandbox() {}
	~Sandbox() {}

};

ZPH::Application* ZPH::CreateApplication()
{
	return new Sandbox();
}