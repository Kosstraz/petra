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

#ifndef PETRA_HPP
#define PETRA_HPP

# include "petra.h"
# include <nsl.h>
# include "Venus.h"
# include "Gestalt/Gestalt.h"

namespace Petra
{
	FORCEINLINE
	void
	Init(void)
	{
		Venus::Init();
		VVenus::Init(PETRA_ENGINE_NAME, PETRA_VERSION_MAJOR, PETRA_VERSION_MINOR, PETRA_VERSION_PATCH);
		Gestalt::Begin();
	}

	FORCEINLINE
	void
	Loop(void)
	{
		Window*	w = new Window("Fenêtre - PETRA", 800, 600);
		VVenus::SetMainWindow(w);
		Sleep::ForSeconds(1);
		delete (w);
	}

	FORCEINLINE
	void
	Destroy(void)
	{
		Gestalt::End();
		VVenus::Destroy();
		Venus::Destroy();
		Gestalt::DestroyObjects();
	}
}

#endif
