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

#include "../includes/Venus.hpp"
#include "../errors.h"
#include <iostream>
#include <cstdlib>

int
Venus::mainScreenNumber = 0;
xcb_connection_t*
Venus::xcb = nullptr;
const xcb_setup_t*
Venus::setup = nullptr;
xcb_screen_t**
Venus::screens = nullptr;
xcb_screen_t*
Venus::mainScreen = nullptr;

void
Venus::Init(void)
{
	xcb_screen_iterator_t	screenIt;

	Venus::xcb = xcb_connect(NULL, &Venus::mainScreenNumber);
	if (xcb_connection_has_error(Venus::xcb) != 0)
		exit(XCB_CONNECTION_ERROR);
	Venus::setup = xcb_get_setup(Venus::xcb);
	screenIt = xcb_setup_roots_iterator(Venus::setup);
	Venus::mainScreen = screenIt.data;
}

void
Venus::Destroy(void)
{
	xcb_disconnect(Venus::xcb);
	free(Venus::screens);
}

const xcb_setup_t*
Venus::GetSetupInfo(void)
{
	return (Venus::setup);
}
