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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}