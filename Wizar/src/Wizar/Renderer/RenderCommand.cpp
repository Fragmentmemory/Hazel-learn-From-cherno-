#include "wzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wizar {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}