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
		//设置当前线程的OpenGL上下文, 他告诉程序当前在那个窗口(或上下文)上渲染
		glfwMakeContextCurrent(m_WindowHandle);

		//初始化glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WZ_CORE_ASSERT(status, "Failed to initialize Glad!"); 

		WZ_CORE_INFO("OpenGL Info:");
		WZ_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		WZ_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		WZ_CORE_INFO("	Version: {0}",glGetString(GL_VERSION));

#ifdef WZ_ENABLE_ASSERTS //添加了对 OpenGL 版本的检查
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		WZ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}