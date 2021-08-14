#include "zphpch.h"
#include "WindowsInput.h"

#include "Zephirus/Application.h"
#include <GLFW/glfw3.h>


namespace ZPH
{
	Input* Input::s_Instance = new WindowsInput();

	bool ZPH::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool ZPH::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> ZPH::WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos; // <--- May Cause performance issues
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos};
	}

	float ZPH::WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float ZPH::WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}