#include <wizar.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Wizar::Layer
{


public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Wizar::VertexArray::Create());

		// Index Buffer
		float vertices[3 * 7] = {
			-0.5f,-0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f,-0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		//创建顶点缓冲
		std::shared_ptr<Wizar::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Wizar::VertexBuffer::Create(vertices, sizeof(vertices)));

		//设置布局(顶点属性设置)
		Wizar::BufferLayout layout = {
					{Wizar::ShaderDataType::Float3, "a_Position"},
					{Wizar::ShaderDataType::Float4, "a_Color"}
		};
		//保存设置
		vertexBuffer->SetLayout(layout);
		//将其添加入顶点数组中进行管理
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Wizar::IndexBuffer>indexBuffer;
		indexBuffer.reset(Wizar::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Wizar::VertexArray::Create());

		//蓝色正方形顶点
		float squareVertices[3 * 4] = {
				-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Wizar::VertexBuffer>squareVB;
		squareVB.reset(Wizar::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Wizar::ShaderDataType::Float3,"a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<Wizar::IndexBuffer>squareIB;
		squareIB.reset(Wizar::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);



		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position; 
			layout(location = 1) in vec4 a_Color; 

			uniform mat4 u_ViewProjection;	
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string framentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;			
			in vec4 v_Color;			

			void main()
			{
				color = v_Color;
			}
		)";
		m_Shader.reset(new Wizar::Shader(vertexSrc, framentSrc));
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position; 
				
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";
		std::string blueShaderFramentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;		

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new Wizar::Shader(blueShaderVertexSrc, blueShaderFramentSrc));
	}

	void OnUpdate(Wizar::TimeStep ts) override
	{
		if (Wizar::Input::IsKeyPressed(WZ_KEY_LEFT))
 			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
 		else if (Wizar::Input::IsKeyPressed(WZ_KEY_RIGHT))
 			m_CameraPosition.x += m_CameraMoveSpeed * ts;
 
 		if (Wizar::Input::IsKeyPressed(WZ_KEY_UP))
 			m_CameraPosition.y += m_CameraMoveSpeed * ts;
 		else if (Wizar::Input::IsKeyPressed(WZ_KEY_DOWN))
 			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
 
 		if (Wizar::Input::IsKeyPressed(WZ_KEY_A))
 			m_CameraRotation += m_CameraRotationSpeed * ts;
 		if (Wizar::Input::IsKeyPressed(WZ_KEY_D))
 			m_CameraRotation -= m_CameraRotationSpeed * ts;

 		Wizar::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
 		Wizar::RenderCommand::Clear();
 
 		m_Camera.SetPosition(m_CameraPosition);
 		m_Camera.SetRotation(m_CameraRotation);
 
 		Wizar::Renderer::BeginScene(m_Camera);
 
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Wizar::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}
 		Wizar::Renderer::Submit(m_Shader, m_VertexArray);
 
 		Wizar::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
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
	private:
		std::shared_ptr<Wizar::Shader> m_Shader;
		std::shared_ptr<Wizar::VertexArray> m_VertexArray;

		std::shared_ptr<Wizar::Shader> m_BlueShader;
		std::shared_ptr<Wizar::VertexArray> m_SquareVA;

		Wizar::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 5.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;
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