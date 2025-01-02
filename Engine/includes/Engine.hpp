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
/*                                              ███    ███             		*/
/*																			*/
/************************************************************************** */

#ifndef PETRA_ENGINE_HPP
#define PETRA_ENGINE_HPP

# include <nsl.h>
# include <vector>
# include <vulkan/vulkan.hpp>
# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>
# include "Window.hpp"

struct Engine
{
	static
	void
	Init(void);

	static
	void
	Loop(void);

	static
	void
	PauseLoop(void);

	static
	void
	MakePause(void);

	static
	void
	MakePlay(void);

	static
	void
	Destroy(void);

	static
	void
	Debug(void);

	static int					errorCode;
	static bool					isInitialized;
	static bool					isPaused;
	static bool					isDestroyed;
	static bool					requestQuiting;
	static Window*				mainWindow;
	//static std::vector<Window*>	windows;
	static double				deltaTime;
};

#endif
