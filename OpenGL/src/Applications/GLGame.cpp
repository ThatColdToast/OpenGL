#include <iostream>
#include <string>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "GLCall.h"
#include "Profiling.h"
#include "Timing.h"

int main_GLGame(void)
{
	Instrumentor::Get().BeginSession("Init", "init.json");

	/* GLFW INIT */
	GLFWwindow* window;
    int screenWidth = 940, screenHeight = 540;

	 // ImGui_ImplOpenGL3_Init();
	
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
		window = glfwCreateWindow(screenWidth, screenHeight, "Hello Window", NULL, NULL);
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
		// float positions[] = {
		// 	-50.0f, -50.0f, 0.0f, 0.0f, // 0
		// 	 50.0f, -50.0f, 1.0f, 0.0f, // 1
		// 	 50.0f,  50.0f, 1.0f, 1.0f, // 2
		// 	-50.0f,  50.0f, 0.0f, 1.0f  // 3
		// };

		// unsigned int indices[] =
		// {
		// 	0, 1, 2,
		// 	2, 3, 0
		// };

        /* OpenGL Viewport */
        GLCall(glViewport(0, 0, screenWidth, screenHeight));

		/* OpenGL Blending Mode */
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Timer timer;

		while (!glfwWindowShouldClose(window))
		{
			timer.UpdateTime();

			if(timer.frameNumber() % 30 == 0) std::printf("fps(%.0f)\n", timer.frameRateSmooth());

            {
				/* Poll for and process events */
				glfwPollEvents();
				glfwGetWindowSize(window, &screenWidth, &screenHeight);
			}

			/* Update Scene */

			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            // GLCall(glClear(GL_COLOR_BUFFER_BIT));

			{
				/* Swap front and back buffers */
				glfwSwapBuffers(window);
			}
		}
	}

	glfwTerminate();
	return 0;
}