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
		while (w->IsOpened())
		{
			std::cout << "ah\n";
			w->RecvLocalEvent(XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT, w->GetAtom("WM_ATOM"), 1, WindowState::Invisible);
			//w->Close();
		}
		//while (1) ;
		Sleep::ForSeconds(3);
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
