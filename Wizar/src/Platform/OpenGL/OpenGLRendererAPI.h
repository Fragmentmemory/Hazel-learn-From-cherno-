#pragma once
#include "Wizar/Renderer/RendererAPI.h"

namespace Wizar {
	class OpenGLRendererAPI:public RendererAPI
	{
	public:
		//≥ı ºªØ
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}


