#pragma once


#include "Zephirus/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace ZPH {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandle;
	};
}