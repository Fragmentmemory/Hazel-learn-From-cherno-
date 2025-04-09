#pragma once

#include "Wizar/Layer.h"

#include "Wizar/Events/Event.h"
#include "Wizar/Events/MouseEvent.h"
#include "Wizar/Events/KeyEvent.h"
#include "Wizar/Events/ApplicationEvent.h"


//构建引擎自己的ui界面
namespace Wizar {
	class Wizar_API ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}

