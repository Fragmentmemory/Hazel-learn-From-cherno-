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

		//��Ӷ��㻺��
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		//���û�����������
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;
		//��ȡ���㻺��
		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers()const { return m_VertexBuffers; }
		//��ȡ������������
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}

