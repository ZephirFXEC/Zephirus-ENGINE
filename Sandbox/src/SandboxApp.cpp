#include <Zephirus.h>

class ExampleLayer : public ZPH::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		ZPH_INFO("ExampleLayer::Update");
	}

	void OnEvent(ZPH::Event& event) override
	{
		ZPH_TRACE("{0}", event);
	}

};

class Sandbox : public ZPH::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ZPH::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

ZPH::Application* ZPH::CreateApplication()
{
	return new Sandbox();
}