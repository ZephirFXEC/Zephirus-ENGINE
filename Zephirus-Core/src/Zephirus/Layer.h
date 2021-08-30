#pragma once

#include "Zephirus/Core.h"
#include "Zephirus/Core/Timestep.h"
#include "Zephirus/Events/Event.h"

namespace ZPH {

	class ZPH_API Layer 
	{
	public:
		Layer(const std::string& name = "layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}