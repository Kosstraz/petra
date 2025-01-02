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

#include "Engine.hpp"
#include "../platform.h"
#include "GestaltCore.hpp"
#include "../CHRONO/Chrono.hpp"

bool
Engine::isInitialized = false;
bool
Engine::isPaused = false;
bool
Engine::isDestroyed = false;
bool
Engine::requestQuiting = false;
Window*
Engine::mainWindow = nullptr;
//std::vector<Window*>
//Engine::windows = std::vector<Window*>();
double
Engine::deltaTime = 0.0;
int
Engine::errorCode = 0;

void
Engine::Init(void)
{
	glfwInit();
	if (!glfwVulkanSupported())
		exit(PETRA_VULKAN_NOT_SUPPORTED);
	Engine::mainWindow = new Window("Petra - 0.0.1 <==> DEBUG", 800, 600);
	glfwMakeContextCurrent(*Engine::mainWindow);
	/* do some stuff */
	Engine::isInitialized = true;
}

void
TestsLoop(float deltaTime);

void
Engine::Loop(void)
{
	SimpleChrono	deltaTimeChrono;

	Gestalt::Begin();
	while (Engine::mainWindow->IsOpened())
	{
		deltaTimeChrono.SnapStart();
		glfwPollEvents();
		glfwSwapBuffers(*Engine::mainWindow);
		deltaTimeChrono.SnapEnd();
		Engine::deltaTime = deltaTimeChrono.GetElapsedTime();
		Gestalt::Consciousness(Engine::deltaTime);
		TestsLoop(Engine::deltaTime);
		std::cout << "ahah\n";
	}
	Gestalt::End();
	Gestalt::DestroyObjects();
}
void
Engine::PauseLoop(void)
{
	while (Engine::mainWindow->IsOpened() && Engine::isPaused)
	{
		glfwPollEvents();
		glfwSwapBuffers(*Engine::mainWindow);
	}
}

void
Engine::MakePause(void)
{
	Engine::isPaused = true;
	Engine::PauseLoop();
}

void
Engine::MakePlay(void)
{
	Engine::isPaused = false;
}

void
Engine::Destroy(void)
{
	glfwTerminate();
	/* do some stuff */
	Engine::isDestroyed = true;
}

void
Engine::Debug(void)
{
	Engine::Init();
	Engine::Loop();
	//Engine::Destroy();
}
