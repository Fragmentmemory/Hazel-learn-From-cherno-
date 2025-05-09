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

		virtual void OnAttach() {}//���㱻���͵���ջ��,�͹̶���
		virtual void OnDetach(){}//����Ӳ�ջ���Ƴ�ʱ,���Ƿ�����
		virtual void OnUpdate(TimeStep ts) {}//�������ʱ,Application���ô˺���,�˺���������ÿһ֡ 
		virtual void OnEvent(Event& event) {}//���ڽ����м����¼�
		virtual void OnImGuiRender(){}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

