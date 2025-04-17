#pragma once
#include "Wizar/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Wizar{
	class OpenGLContext :
		public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);


		void Init() override;


		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}

