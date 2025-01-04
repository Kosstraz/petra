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
