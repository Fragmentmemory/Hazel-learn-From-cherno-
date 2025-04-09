#include <Wizar.h>

#include "imgui/imgui.h"

class ExampleLayer : public Wizar::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Wizar::Input::IsKeyPressed(WZ_KEY_TAB))
			WZ_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("hello world");
		ImGui::ColorEdit4("", new float[4]);
		ImGui::End();
	}

	void OnEvent(Wizar::Event& event) override
	{
		if (event.GetEventType() == Wizar::EventType::KeyPressed)
		{
			Wizar::KeyPressedEvent& e = (Wizar::KeyPressedEvent&)event;
			if (e.GetKeyCode() == WZ_KEY_TAB)
				WZ_TRACE("Tab key is pressed (event)!");
			WZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Wizar::Application
{
public:
	Sandbox()
	{
		PushOverlay(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Wizar::Application* Wizar::CreateApplication()
{
	return new Sandbox();
}