#include "TestTextureImGui.h"

#include "vendor/imgui/imgui.h"
#include "vendor/cherno/Instrumentor.h"

#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	TestTextureImGui::TestTextureImGui()
		: translationA(200, 200, 0), translationB(400, 200, 0)
	{
	}

	TestTextureImGui::~TestTextureImGui()
	{
	}

	void TestTextureImGui::OnUpdate(float deltaTime)
	{
		/*{
			PROFILE_SCOPE("Set 1st Uniform Mat4");
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);
		}

		{
			PROFILE_SCOPE("Set 2nd Uniform Mat4");
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(va, ib, shader);
		}*/
	}

	void TestTextureImGui::OnRender()
	{
	}

	void TestTextureImGui::OnImGuiRender()
	{
		PROFILE_SCOPE("ImGui State");
		ImGui::Begin("Hello, world!");
		ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}