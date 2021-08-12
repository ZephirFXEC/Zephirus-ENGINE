#pragma once

#include "Zephirus/Layer.h"
#include "Zephirus/Events/KeyEvent.h"
#include "Zephirus/Events/MouseEvent.h"
#include "Zephirus/Events/ApplicationEvent.h"

namespace ZPH {

	class ZPH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleaseEvent(KeyReleaseEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	
	private:
		float m_Time = 0.0f;
	};

}