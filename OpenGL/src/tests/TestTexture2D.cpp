#include "TestTexture2D.h"

#include <GL/glew.h>

#include "Profiling.h"

#include "GLCall.h"
#include "vendor/imgui/imgui.h"

#include "vendor/glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		PROFILE_FUNCTION();

		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, // 0
			 50.0f, -50.0f, 1.0f, 0.0f, // 1
			 50.0f,  50.0f, 1.0f, 1.0f, // 2
			-50.0f,  50.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		/* OpenGL Blending Mode */
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);
		m_Texture = std::make_unique<Texture>("res/textures/dirt.png");

		m_VAO = std::make_unique<VertexArray>();
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2); // Push 2 Positions ()
		layout.Push<float>(2); // Push 2 TexCoords
		m_VAO->AddBuffer(vb, layout);

		//IndexBuffer ib(indices, 6);
		//m_IBO(indices, 6);

		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		//Shader shader("res/shaders/Basic.shader");
		m_Shader->Bind();

		//Texture texture("res/textures/dirt.png");
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		m_VAO->Unbind();
		vb.Unbind();
		m_IBO->Unbind();
		m_Shader->Unbind();
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		{
			PROFILE_SCOPE("Set 1st Uniform Mat4");
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = proj * view * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}

		{
			PROFILE_SCOPE("Set 2nd Uniform Mat4");
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = proj * view * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		PROFILE_FUNCTION("ImGui State");
		ImGui::Begin("Hello, world!");
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}