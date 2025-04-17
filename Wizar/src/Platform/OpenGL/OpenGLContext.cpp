#include "Wzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Wizar {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		WZ_CORE_ASSERT(windowHandle, "windowHandle is null!");
	}

	void OpenGLContext::Init()
	{
		//���õ�ǰ�̵߳�OpenGL������, �����߳���ǰ���Ǹ�����(��������)����Ⱦ
		glfwMakeContextCurrent(m_WindowHandle);

		//��ʼ��glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WZ_CORE_ASSERT(status, "Failed to initialize Glad!"); 

		WZ_CORE_INFO("OpenGL Info:");
		WZ_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		WZ_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		WZ_CORE_INFO("	Version: {0}",glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}