#pragma once

#include "RendererAPI.h"

namespace ZPH
{
	class RenderCommand
	{
	public:

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}


	private:
		static RendererAPI* s_RendererAPI;
	};
}