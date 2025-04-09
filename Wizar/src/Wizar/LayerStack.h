#pragma once

#include "Wizar/Core.h"
#include "Layer.h"

namespace Wizar {
	//��LayerStack����������һ�����������װ����Щ��������������飩����ǡ�
	//	overlay3 ĳһ������ͼ��
	//	overlay2 ����ͼ��
	//	overlay1 �˵�ͼ��
	//	layer1 ��Ϸ�е�UI����ɱ����ʱ��ʾ��ͼ�꣩
	//	layer2 ��Ϸ��ɫ
	//	layer3 ��Ϸ����
	class Wizar_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}

