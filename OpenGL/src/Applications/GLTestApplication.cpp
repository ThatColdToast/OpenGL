#include <iostream>
#include <string>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

// #include "imgui/imgui.h"
// #include "imgui/imgui_impl_opengl3.h"
// #include "imgui/imgui_impl_glfw.h"

#include "Graphics/GLCall.h"

int main_GLTestApplication(void)
{
	/* GLFW INIT */
	GLFWwindow* window;
	int width = 960, height = 540;

	 // ImGui_ImplOpenGL3_Init();
	
	{
		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 
	}

	{
		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(width, height, "Hello Window", NULL, NULL);
	}

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	{
		if (!window)
		{
            std::cout << "Error: glfwCreateWindow()" << std::endl; 
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(0); // Turn Vsync on
	}

	/* GLEW INIT */
	{
        glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
        {
			std::cout << "Error: glewInit()" << std::endl; // uta.edu/admissions
            return -1;
        }

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

        /* OpenGL Viewport */
        GLCall(glViewport(0, 0, screenWidth, screenHeight));

		/* OpenGL Blending Mode */
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		auto start_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
		double smoothDeltaTime = start_time.count() - start_time.count();
		long frameNumber = 0;

		while (!glfwWindowShouldClose(window))
		{
			frameNumber++;
			auto current_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
			double deltaTime = current_time.count() - start_time.count();
			start_time = current_time;

			smoothDeltaTime = ((smoothDeltaTime * 99.0) + deltaTime) / 100.0;
			double smoothFPS = (1000000.0 / smoothDeltaTime);

			// std::printf("dt(%f) smooth dt(%f)\n", deltaTime, smoothDeltaTime);

			// 10 Times per second, print fps
			// if(frameNumber % ((int)(smoothFPS) / 10) == 0) std::printf("fps(%.0f)\n", smoothFPS);
			if(frameNumber % 30 == 0) std::printf("fps(%.0f)\n", smoothFPS);

            {
				/* Poll for and process events */
				glfwPollEvents();
			}

			//glfwGetWindowSize(window, &width, &height);

			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

			{
				/* Swap front and back buffers */
				glfwSwapBuffers(window);
			}
		}
	}

	glfwTerminate();
	return 0;
}