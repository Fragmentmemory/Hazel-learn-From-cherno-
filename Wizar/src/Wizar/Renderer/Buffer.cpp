#include "wzpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Wizar {

	Wizar::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			WZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		WZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Wizar::IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			WZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(Indices, size);
		}

		WZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}