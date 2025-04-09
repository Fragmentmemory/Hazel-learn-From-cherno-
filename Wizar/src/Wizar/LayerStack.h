#pragma once

#include "Wizar/Core.h"
#include "Layer.h"

namespace Wizar {
	//“LayerStack”本质上是一个包裹（或封装）这些层的向量（或数组）的外壳。
	//	overlay3 某一设置项图层
	//	overlay2 设置图层
	//	overlay1 菜单图层
	//	layer1 游戏中的UI（击杀敌人时显示的图标）
	//	layer2 游戏角色
	//	layer3 游戏背景
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

