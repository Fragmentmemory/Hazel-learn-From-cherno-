#pragma once

#include "Wizar/Renderer/VertexArray.h"
namespace Wizar {
	class OpenGLVertexArray:public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;


		void Unbind() const override;

		//添加顶点缓冲
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		//设置缓冲索引缓冲
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;
		//获取顶点缓冲
		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()const { return m_VertexBuffers; }
		//获取缓冲索引缓冲
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}

