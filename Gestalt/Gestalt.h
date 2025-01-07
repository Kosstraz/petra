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

#ifndef PETRA_GESTALT_H
#define PETRA_GESTALT_H

# include "includes/Gestalt.hpp"

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
