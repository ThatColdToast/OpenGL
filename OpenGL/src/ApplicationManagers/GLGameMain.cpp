#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Graphics/GLCall.h"

#define PROFILING 1
#include "Utils/Profiling.h"
#include "Utils/Timing.h"

int main_GLGame(void)
{
    Instrumentor::Get().BeginSession("Init", "init.json");
	Timer g_GameTimer;

	/* GLFW INIT */
	GLFWwindow* window;
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
		// float vertices[] = {
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

		Instrumentor::Get().EndSession();
		Instrumentor::Get().BeginSession("Loop", "loop.json");
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			PROFILE_SCOPE("Window Loop");
			g_GameTimer.UpdateTime();

			if(g_GameTimer.frameNumber() % 100 == 0) std::printf("fps(%.2f)\n", g_GameTimer.frameRateSmooth());

			/* Poll for and process events */
            {
				PROFILE_SCOPE("Poll For Events");
				glfwPollEvents();
				glfwGetWindowSize(window, &screenWidth, &screenHeight);
			}

			/* Update Scene */
			{
				PROFILE_SCOPE("Update Scene");
			}
			

			/* Render Scene */
			{
				PROFILE_SCOPE("Render Scene");
				GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            	// GLCall(glClear(GL_COLOR_BUFFER_BIT));
			}

			/* Swap front and back buffers */
			{
				PROFILE_SCOPE("Swap Buffers");
				glfwSwapBuffers(window);
			}
		}
	}
	Instrumentor::Get().EndSession();

	glfwTerminate();
	return 0;
}