#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

namespace zephirus::graphics {

	class Window {
	public:

		Window(const char* title, int width, int height);
		~Window();
		void clear() const;
		void update();
		bool closed() const;

		inline int getWidth() { return m_Width; }
		inline int getHeight() { return m_Height; }

	private:
		const char* m_Title;
		int m_Width, m_Height;
		bool m_Closed;
		GLFWwindow* m_Window;

	private:
		bool Init();
	};

}