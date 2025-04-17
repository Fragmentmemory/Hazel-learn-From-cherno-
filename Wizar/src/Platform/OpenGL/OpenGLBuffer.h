#pragma once
#include "Wizar/Renderer/Buffer.h"

namespace Wizar
{
	class OpenGLVertexBuffer :
	    public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		void Bind()const override;

		void Unbind()const override;


		const BufferLayout& GetLayout() const override;
		void SetLayout(const BufferLayout& layout) override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer :
		public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* Indices, uint32_t count);
		~OpenGLIndexBuffer();

		void Bind()const override;

		void Unbind()const override;


		uint32_t GetCount() const { return m_Count; };

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}

