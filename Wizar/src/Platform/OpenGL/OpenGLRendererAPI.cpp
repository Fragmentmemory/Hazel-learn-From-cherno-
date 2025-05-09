#include "wzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Wizar {
	//初始化OpenGL
	void OpenGLRendererAPI::Init()
	{
		//默认情况下 OpenGL 会直接覆盖像素颜色，启用混合后允许新颜色与已有颜色按特定规则混合
		glEnable(GL_BLEND);
		//设置混合方程参数 最终颜色 = (源颜色 × 源.alpha) + (目标颜色 × (1 - 源.alpha))
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
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