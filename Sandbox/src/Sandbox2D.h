#pragma once

#include "Wizar.h"

class Sandbox2D : public Wizar::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Wizar::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Wizar::Event& e) override;
private:
	Wizar::OrthographicCameraController m_CameraController;

	// Temp
	Wizar::Ref<Wizar::VertexArray> m_SquareVA;
	Wizar::Ref<Wizar::Shader> m_FlatColorShader;

	Wizar::Ref<Wizar::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};