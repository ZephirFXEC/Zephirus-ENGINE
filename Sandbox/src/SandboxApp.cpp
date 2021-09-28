#include <Zephirus.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public ZPH::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(ZPH::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0, 0.8f, 0.2f, 0.8f, 1.0f,
			  0.f,  0.5f, 0, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0, 0.8f, 0.8f, 0.2f, 1.0f
		};

		ZPH::Ref<ZPH::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ZPH::VertexBuffer::Create(vertices, sizeof(vertices)));

		ZPH::BufferLayout layout = {
			{ ZPH::ShaderDataType::Float3, "a_Position"},
			{ ZPH::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		ZPH::Ref<ZPH::IndexBuffer> indexBuffer;
		indexBuffer.reset(ZPH::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(ZPH::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		ZPH::Ref<ZPH::VertexBuffer> squareVB;
		squareVB.reset(ZPH::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ZPH::ShaderDataType::Float3, "a_Position" },
			{ ZPH::ShaderDataType::Float2, "a_TextCoord"}
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ZPH::Ref<ZPH::IndexBuffer> squareIB;
		squareIB.reset(ZPH::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(ZPH::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(ZPH::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(ZPH::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = ZPH::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<ZPH::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<ZPH::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(ZPH::Timestep ts) override
	{
		if (ZPH::Input::IsKeyPressed(ZPH_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ZPH::Input::IsKeyPressed(ZPH_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (ZPH::Input::IsKeyPressed(ZPH_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (ZPH::Input::IsKeyPressed(ZPH_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (ZPH::Input::IsKeyPressed(ZPH_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (ZPH::Input::IsKeyPressed(ZPH_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		ZPH::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ZPH::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ZPH::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ZPH::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ZPH::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ZPH::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		ZPH::Renderer::Submit(m_Shader, m_VertexArray);

		ZPH::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(ZPH::Event& event) override
	{

	}

private:
	ZPH::Ref<ZPH::Shader> m_Shader;
	ZPH::Ref<ZPH::VertexArray> m_VertexArray;

	ZPH::Ref<ZPH::Shader> m_FlatColorShader, m_TextureShader;
	ZPH::Ref<ZPH::VertexArray> m_SquareVA;

	ZPH::Ref<ZPH::Texture2D> m_Texture;

	ZPH::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public ZPH::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

ZPH::Application* ZPH::CreateApplication()
{
	return new Sandbox();
}