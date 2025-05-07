#include "wzpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Wizar {

	VertexArray* VertexArray::Create() 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			WZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		WZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}