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

#ifndef PETRA_WINDOW_HPP
#define PETRA_WINDOW_HPP

# include <xcb/xcb.h>
# include "Venus.hpp"

class Window final : protected Venus
{
public:
	Window(void) = delete;
	Window(const char* title, int width, int height);
	~Window(void);

	void
	ChangeTitle(const char* title);

	void
	ChangeTitle(const char* title, unsigned int size);

	void
	Destroy(void);

private:
	bool			isDestroyed;
	unsigned int	id;
	unsigned int	valueMask;
	unsigned int	valueList[2];

private:
	void
	__ChangeTitle(const char* title, unsigned int size);

	virtual void
	SetTheClassAbstract(void) override
	{}
};

#endif
