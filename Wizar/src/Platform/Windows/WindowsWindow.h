#pragma once

#include "Wizar/Window.h"

#include <GLFW/glfw3.h>

namespace Wizar {
	class WindowsWindow:public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		// Inherited via Window
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; };
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		// ��������
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled)override;
		bool IsVSync() const override;

		//virtual���ӿɶ���, �������Ǽ̳л���ĺ��� 
		virtual void* GetNativeWindow() const { return m_window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}

