/************************************************************************** */
/*																			*/
/*		   ▄███████▄    ▄████████     ███        ▄████████    ▄████████		*/
/*		  ███    ███   ███    ███ ▀█████████▄   ███    ███   ███    ███		*/
/*		  ███    ███   ███    █▀     ▀███▀▀██   ███    ███   ███    ███		*/
/*		  ███    ███  ▄███▄▄▄         ███   ▀  ▄███▄▄▄▄██▀   ███    ███		*/
/*		▀█████████▀  ▀▀███▀▀▀         ███     ▀▀███▀▀▀▀▀   ▀███████████		*/
/*		  ███          ███    █▄      ███     ▀███████████   ███    ███		*/
/*		  ███          ███    ███     ███       ███    ███   ███    ███		*/
/*		 ▄████▀        ██████████    ▄████▀     ███    ███   ███    █▀ 		*/
/*                                              ███    ███              	*/
/*																			*/
/************************************************************************** */

#include "JardinsSuspendus.hpp"
#include "../Engine/CHRONO/Chrono.hpp"
#include "../Engine/platform.h"
#include <sys/wait.h>

float
JardinsSuspendus::deltaTime = 0.0f;
Window*
JardinsSuspendus::mainWindow = nullptr;

void
JardinsSuspendus::Loop(void)
{
	SimpleChrono	deltaTimeChrono;

	while (JardinsSuspendus::mainWindow->IsOpened())
	{
		deltaTimeChrono.SnapStart();
		glfwPollEvents();
		glfwSwapBuffers(*JardinsSuspendus::mainWindow);
		deltaTimeChrono.SnapEnd();
		JardinsSuspendus::deltaTime = deltaTimeChrono.GetElapsedTime();
		if (glfwGetKey(*JardinsSuspendus::mainWindow, GLFW_KEY_Z))
		{
			std::cout << "Z\n";
			Thread	t(Engine::Debug);
			t.Wait();
		}
	}
}

void
JardinsSuspendus::Init()
{
	glfwInit();
	if (!glfwVulkanSupported())
		exit(PETRA_VULKAN_NOT_SUPPORTED);
	JardinsSuspendus::mainWindow = new Window("Petra - 0.0.1", 800, 600);
	glfwMakeContextCurrent(*JardinsSuspendus::mainWindow);
}

void
JardinsSuspendus::Destroy()
{
	glfwTerminate();
}
