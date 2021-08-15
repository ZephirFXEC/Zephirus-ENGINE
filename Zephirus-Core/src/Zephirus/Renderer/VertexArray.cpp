#include "zphpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ZPH
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZPH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		ZPH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}