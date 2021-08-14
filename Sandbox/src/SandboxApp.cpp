#include <Zephirus.h>

#include "imgui/imgui.h"

class ExampleLayer : public ZPH::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (ZPH::Input::IsKeyPressed(ZPH_KEY_TAB))
			ZPH_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(ZPH::Event& event) override
	{
		if (event.GetEventType() == ZPH::EventType::KeyPressed)
		{
			ZPH::KeyPressedEvent& e = (ZPH::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ZPH_KEY_TAB)
				ZPH_TRACE("Tab key is pressed (event)!");
			ZPH_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public ZPH::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

ZPH::Application* ZPH::CreateApplication()
{
	return new Sandbox();
}