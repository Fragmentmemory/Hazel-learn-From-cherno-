#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}//���㱻���͵���ջ��,�͹̶���
		virtual void Detach(){}//����Ӳ�ջ���Ƴ�ʱ,���Ƿ�����
		virtual void OnUpdate() {}//�������ʱ,Application���ô˺���,�˺���������ÿһ֡
		virtual void OnEvent(Event& event) {}//���ڽ����м����¼�

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

