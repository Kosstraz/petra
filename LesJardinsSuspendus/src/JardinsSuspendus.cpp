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
#include "../Helper/Helper.h"
#include <sys/wait.h>

float
JardinsSuspendus::deltaTime = 0.0f;
//Window*
//JardinsSuspendus::mainWindow = nullptr;

void
JSTestsLoop(float deltaTime)
{
	(void)deltaTime;
}

void
JardinsSuspendus::Loop(void)
{
	/*SimpleChrono	deltaTimeChrono;

	while (JardinsSuspendus::mainWindow->IsOpened())
	{
		deltaTimeChrono.SnapStart();
		glfwPollEvents();
		glfwSwapBuffers(*JardinsSuspendus::mainWindow);
		deltaTimeChrono.SnapEnd();
		JardinsSuspendus::deltaTime = deltaTimeChrono.GetElapsedTime();
		JSTestsLoop(JardinsSuspendus::deltaTime);
		if (glfwGetKey(*JardinsSuspendus::mainWindow, GLFW_KEY_Z))
		{
			Engine::Debug();
			glfwMakeContextCurrent(*JardinsSuspendus::mainWindow);
		}
	}*/
}

void
JardinsSuspendus::__SetWindowHints(void)
{
	//glfwDefaultWindowHints();
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void
JardinsSuspendus::__InitVulkan(void)
{
	/*unsigned int			extCount;
	const char** const		extList = glfwGetRequiredInstanceExtensions(&extCount);
	vk::InstanceCreateInfo	vkInfo(vk::InstanceCreateFlags(), nullptr, 0, nullptr, extCount, extList);
	vk::Instance			vulkan = vk::createInstance(vkInfo);
	vk::SurfaceKHR			surf;
	VkSurfaceKHR_T*			psurf = VkSurfaceKHR(&surf);*/
	//glfwCreateWindowSurface(VkInstance(vulkan), *JardinsSuspendus::mainWindow, nullptr, &psurf);
}

void
JardinsSuspendus::__DestroyVulkan(void)
{
	//vkDestroySurfaceKHR((VkInstance)vulkan, VkSurfaceKHR(surf), nullptr);
}

void
JardinsSuspendus::Init()
{
	/*glfwInit();
	if (!glfwVulkanSupported())
		exit(PETRA_VULKAN_NOT_SUPPORTED);
	JardinsSuspendus::__SetWindowHints();
	JardinsSuspendus::mainWindow = new Window("Petra - 0.0.1", 800, 600);
	glfwMakeContextCurrent(*JardinsSuspendus::mainWindow);
	JardinsSuspendus::__InitVulkan();*/
}

void
JardinsSuspendus::Destroy()
{
	//JardinsSuspendus::__DestroyVulkan();
	//glfwTerminate();
}
