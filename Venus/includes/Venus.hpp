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

#ifndef PETRA_VENUS_HPP
#define PETRA_VENUS_HPP

# include <xcb/xcb.h>
# include <vulkan/vulkan.h>

struct Venus
{
public:
	Venus(void)			= default;
	Venus(const Venus&)	= delete;
	Venus(Venus&&)		= delete;
	~Venus(void)		= default;

	static void
	Init(void);

	static void
	Destroy(void);

	static const xcb_setup_t*
	GetSetupInfo(void);

private:
	virtual void
	SetTheClassAbstract(void) = 0;

protected:
	static xcb_screen_t*		mainScreen;
	static xcb_screen_t**		screens;
	static xcb_connection_t*	xcb;
	static const xcb_setup_t*	setup;
	static int					mainScreenNumber;
};

#endif
