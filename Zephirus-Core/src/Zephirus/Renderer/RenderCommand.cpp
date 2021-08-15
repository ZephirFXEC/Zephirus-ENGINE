#include "zphpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace ZPH
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}