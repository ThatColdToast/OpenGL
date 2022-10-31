#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// #include "vendor/imgui/imgui_impl_glfw.h"
// #include "vendor/imgui/imgui_impl_opengl3.h"

#include "Graphics/GLCall.h"

#define PROFILING 0
#include "Utils/Profiling.h"
#include "Utils/Timing.h"

#include "Applications/TestApplication.h"

int main_GLApplication(void)
{
	Instrumentor::Get().BeginSession("Init", "init.json");
	Timer g_GameTimer;

	/* GLFW INIT */
	GLFWwindow *window;
	int screenWidth = 940, screenHeight = 540;

	{
		PROFILE_SCOPE("Init GLFW Library");

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}

	{
		PROFILE_SCOPE("Init Window");

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(screenWidth, screenHeight, "Starting...", NULL, NULL);
	}

	{
		PROFILE_SCOPE("Test GLFW window");

		if (!window)
		{
			std::cout << "Error: glfwCreateWindow()" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Set Vsync (0, 1) */
		glfwSwapInterval(0); // Turn Vsync on
	}

	/* GLEW INIT */
	{
		PROFILE_SCOPE("Init GLEW Library");

		glewExperimental = GL_TRUE; // Unknown

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error: glewInit()" << std::endl; // uta.edu/admissions
			return -1;
		}

		std::cout << "OPENGL VERSION " << glGetString(GL_VERSION) << std::endl;
	}

	{
		// {
		// 	PROFILE_SCOPE("Setup Dear ImGui Context");
		// 	IMGUI_CHECKVERSION();
		// 	ImGui::CreateContext();
		// 	ImGuiIO &io = ImGui::GetIO();
		// 	// Setup Platform/Renderer bindings
		// 	ImGui_ImplGlfw_InitForOpenGL(window, true);
		// 	ImGui_ImplOpenGL3_Init("#version 330 core");
		// 	// Setup Dear ImGui style
		// 	ImGui::StyleColorsDark();
		// }

		/* OpenGL Viewport */
		GLCall(glViewport(0, 0, screenWidth, screenHeight));

		/* OpenGL Blending Mode */
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		/* Create Application Object */
		TestApplication application;

		Instrumentor::Get().EndSession();
		Instrumentor::Get().BeginSession("Loop", "loop.json");


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			PROFILE_SCOPE("Window Loop");
			g_GameTimer.UpdateTime();

			if (g_GameTimer.frameNumber() % 100 == 0)
				std::printf("fps(%.2f)\n", g_GameTimer.frameRateSmooth());

			/* Poll for and process events */
			{
				PROFILE_SCOPE("Poll For Events");
				glfwPollEvents();
				glfwGetWindowSize(window, &screenWidth, &screenHeight);
			}

			// /* ImGui New Frame */
			// {
			// 	PROFILE_SCOPE("ImGui New Frame");
			// 	// Feed inputs to dear imgui, start new frame
			// 	ImGui_ImplOpenGL3_NewFrame();
			// 	ImGui_ImplGlfw_NewFrame();
			// 	ImGui::NewFrame();
			// }

			/* Update Scene */
			{
				PROFILE_SCOPE("Update Scene");
				application.OnUpdate(g_GameTimer);
			}

			/* Render Scene */
			{
				PROFILE_SCOPE("Render Scene");
				GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
				// GLCall(glClear(GL_COLOR_BUFFER_BIT));

				application.OnRender();
			}

			// /* ImGui Create Gui */
			// {
			// 	PROFILE_SCOPE("ImGui Create Gui");
			// 	ImGui::Begin("Demo window");
			// 	ImGui::Button("Hello!");
			// 	ImGui::End();
			// }

			// /* ImGui Render */
			// {
			// 	PROFILE_SCOPE("ImGui Render");
			// 	ImGui::Render();
			// 	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			// }

			/* Swap front and back buffers */
			{
				PROFILE_SCOPE("Swap Buffers");
				glfwSwapBuffers(window);
			}
		}
	}
	Instrumentor::Get().EndSession();

	// ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}