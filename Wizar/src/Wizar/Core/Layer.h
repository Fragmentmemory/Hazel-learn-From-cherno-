#pragma once

#include "Wizar/Core/Core.h"
#include "Wizar/Core/TimeStep.h"
#include "Wizar/Events/Event.h"

namespace Wizar {
	class WIZAR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}//当层被推送到层栈上,就固定他
		virtual void OnDetach(){}//当层从层栈上移除时,我们分离他
		virtual void OnUpdate(TimeStep ts) {}//当层更新时,Application调用此函数,此函数作用于每一帧 
		virtual void OnEvent(Event& event) {}//用于接收中间层的事件
		virtual void OnImGuiRender(){}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

