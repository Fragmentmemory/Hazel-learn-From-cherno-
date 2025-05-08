#include "wzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Wizar {
	//��ʼ��OpenGL
	void OpenGLRendererAPI::Init()
	{
		//Ĭ������� OpenGL ��ֱ�Ӹ���������ɫ�����û�Ϻ���������ɫ��������ɫ���ض�������
		glEnable(GL_BLEND);
		//���û�Ϸ��̲��� ������ɫ = (Դ��ɫ �� Դ.alpha) + (Ŀ����ɫ �� (1 - Դ.alpha))
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}