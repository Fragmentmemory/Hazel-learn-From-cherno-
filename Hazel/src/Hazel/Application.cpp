#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"
#include <glad/glad.h>

namespace Hazel {
//ռλ�� `_1` ��ʾ������������󶨺���ʱ��`x` �����ĵ�һ���������ɵ����ߴ��롣
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		//ʹ��OnEvent����m_Window��EventCallback,��ʹ��ռλ�� `_1`����OnEvent�Ĳ���:Event& e
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		//
	}
	Application::~Application()
	{
	}

	

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PopOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		//HZ_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);//�Ӻ���ǰ�����¼�,���һ����overlay
			if(e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{
		
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}