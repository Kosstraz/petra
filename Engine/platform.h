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

#ifndef PETRA_PLATFORM_H
#define PETRA_PLATFORM_H

# include "GestaltCore.hpp"
# include "Engine.hpp"

# define PETRA_SUCCESS				0
# define PETRA_VULKAN_NOT_SUPPORTED	1

# define GESTALT_NONE
# define GESTALT_USE
# define GESTALT_ACTIVE(classT, ...)								\
	static const bool	PV_GestaltCreate##classT##Wizard = []		\
	{	 															\
		Gestalt::gameObjects.push_back								\
		(															\
			reinterpret_cast<Gestalt *>(new classT(__VA_ARGS__))	\
		);															\
		return (true);												\
	}();															\

#endif
