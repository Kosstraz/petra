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
	//static Window*	mainWindow;
	//static Window*	settingsWindow;

private:
	static void
	__InitVulkan(void);

	static void
	__SetWindowHints(void);

	static void
	__DestroyVulkan(void);
};

#endif
