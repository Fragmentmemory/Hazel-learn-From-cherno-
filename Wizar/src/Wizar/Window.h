#pragma once

#include "Wzpch.h"

#include "Wizar/Core.h"
#include "Wizar/Events/Event.h"

namespace Wizar {
	//窗口的属性
	struct WindowProps
	{
		std::string Title;//标题
		unsigned int Width;//宽度
		unsigned int Height;//高度

		WindowProps(const std::string& title = "Wizar Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			:Title(title),Width(width),Height(height){}
	};

	//基于桌面系统窗口的接口
	class Wizar_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// 窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		// 提升移植性,保证使用其他类似窗口库时一样返回
		virtual void* GetNativeWindow()const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}