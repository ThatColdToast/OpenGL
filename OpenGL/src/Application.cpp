#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "Profiling.h"

#include "tests/Test.h"
#include "tests/TestClearColor.h"

int main(void)
{
	Instrumentor::Get().BeginSession("Init", "init.json");
	/* GLFW INIT */
	GLFWwindow* window;
	int width = 960, height = 540;

	 // ImGui_ImplOpenGL3_Init();
	
	{
		PROFILE_SCOPE("Init GLFW Library");

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	{
		PROFILE_SCOPE("Init Window");
		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	}

	{
		PROFILE_SCOPE("Test GLFW window");
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(1); // Turn Vsync on
	}

	/* GLEW INIT */
	{
		PROFILE_SCOPE("Init GLEW Library");
		if (glewInit() != GLEW_OK)
			std::cout << "Error: glewInit()" << std::endl; // uta.edu/admissions

		std::cout << "OPENGL VERSION " << glGetString(GL_VERSION) << std::endl;
	}

	{
		//float positions[] = {
		//	-50.0f, -50.0f, 0.0f, 0.0f, // 0
		//	 50.0f, -50.0f, 1.0f, 0.0f, // 1
		//	 50.0f,  50.0f, 1.0f, 1.0f, // 2
		//	-50.0f,  50.0f, 0.0f, 1.0f  // 3
		//};

		//unsigned int indices[] =
		//{
		//	0, 1, 2,
		//	2, 3, 0
		//};

		/* OpenGL Blending Mode */
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//VertexArray va;

		//VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push<float>(2); // Push 2 Positions ()
		//layout.Push<float>(2); // Push 2 TexCoords
		//va.AddBuffer(vb, layout);

		//IndexBuffer ib(indices, 6);


		//// shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
		//glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		//Shader shader("res/shaders/Basic.shader");
		//shader.Bind();

		//Texture texture("res/textures/dirt.png");
		//texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

		//va.Unbind();
		//vb.Unbind();
		//ib.Unbind();
		//shader.Unbind();

		ImGui::CreateContext();

		ImGui::StyleColorsDark();



		ImGui_ImplGlfw_InitForOpenGL(window, true);

		const char* glsl_version = "#version 330 core";
		ImGui_ImplOpenGL3_Init(glsl_version);


		// Our state
		/*bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);*/

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");

		Renderer renderer;

		Instrumentor::Get().EndSession();
		Instrumentor::Get().BeginSession("Loop", "loop.json");
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			PROFILE_SCOPE("Render");
			//glfwGetWindowSize(window, &width, &height);

			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			//shader.Bind();
			// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

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
			}

			{
				PROFILE_SCOPE("ImGui State");
				ImGui::Begin("Hello, world!");
				ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}*/

			{
				PROFILE_SCOPE("ImGui Render");
				// Start the Dear ImGui frame
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				if (currentTest)
				{
					currentTest->OnUpdate(0.0f);
					currentTest->OnRender();

					ImGui::Begin("Tests");
					if (currentTest != testMenu && ImGui::Button("<-"))
					{
						delete currentTest;
							currentTest = testMenu;
					}

					currentTest->OnImGuiRender();
					ImGui::End();
				}

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}

			{
				PROFILE_SCOPE("Swap Buffers");
				/* Swap front and back buffers */
				glfwSwapBuffers(window);
			}

			{
				PROFILE_SCOPE("GLFW Poll Events");
				/* Poll for and process events */
				glfwPollEvents();
			}
		}
	}
	Instrumentor::Get().EndSession();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}