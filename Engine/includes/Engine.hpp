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
	//static Window*				mainWindow;
	//static std::vector<Window*>	windows;
	static double				deltaTime;

private:
	static void
	__Debug(void);
};

#endif
