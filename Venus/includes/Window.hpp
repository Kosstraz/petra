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

#ifndef VENUS_WINDOW_HPP
#define VENUS_WINDOW_HPP

	// Withdrawn -> Correspond à l'état où la fenêtre n'est plus dans le gestionnaire de fenêtre
# define CLIENT_MSG_EVENT_DATA32_WITHDRAWN	0
	// Normal -> Correspond à l'état où la fenêtre est affichée normalement
# define CLIENT_MSG_EVENT_DATA32_NORMAL		1
	// Iconic -> Correspond à l'état où la fenêtre est minimisée
# define CLIENT_MSG_EVENT_DATA32_ICONIC		2

# include <xcb/xcb.h>
# include "Venus.hpp"

typedef xcb_atom_t			WAtom;
typedef xcb_generic_event_t	WEvent;
typedef xcb_event_mask_t	WEventMask;

enum class WindowState
{
	Invisible = 0,
	Normal = 1,
	Iconic = 2
};

class Window final : private Venus
{
public:
	Window(void) = delete;
	Window(const char* pTitle, int pWidth, int pHeight);
	~Window(void);

	void
	Poll(void);

	bool
	IsOpened(void);

	bool
	IsClosed(void);

	WAtom
	GetAtom(const char* pAtomName);

// Envoyer un évènement à la fenêtre actuelle
// @param pFlagWhen: Type -> enum xcb_event_mask_t
// @param pAtomAction:
// @param state: true/false
	void
	RecvLocalEvent(int pFlagWhen, WAtom pEventAction, unsigned int pState, WindowState pWState);

	void
	Close(void);

	void
	Open(void);

	void
	ChangeTitle(const char* pTitle);

	void
	ChangeTitle(const char* pTitle, unsigned int pSize);

	void
	Destroy(void);

	unsigned int
	GetXcbID(void);

private:
	bool			isDestroyed;
	bool			isOpened;
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
