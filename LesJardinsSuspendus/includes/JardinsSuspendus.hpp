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

#ifndef PETRA_JARDINSSUSPENDUS_HPP
#define PETRA_JARDINSSUSPENDUS_HPP

# include "Window.hpp"
# include <vulkan/vulkan.hpp>
# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>

class JardinsSuspendus
{
public:
	static void
	Init(void);

	static void
	Loop(void);

	static void
	Destroy(void);

	static float	deltaTime;
	static Window*	mainWindow;
	//static Window*	settingsWindow;
};

#endif
