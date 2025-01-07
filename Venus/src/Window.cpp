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

#include "../includes/Window.hpp"
#include <xcb/xcb.h>
#include <cstring>
#include <cstdlib>

Window::Window(const char* title, int width, int height) :
	isDestroyed(false),
	isOpened(true),
	id(0),
	valueMask(XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK),
	valueList{ Venus::mainScreen->black_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS }
{
	this->id = xcb_generate_id(Venus::xcb);
	xcb_create_window(	Venus::xcb,
						Venus::mainScreen->root_depth,
						this->id,
						Venus::mainScreen->root,
						0,
						0,
						width,
						height,
						10,
						XCB_WINDOW_CLASS_INPUT_OUTPUT,
						Venus::mainScreen->root_visual,
						this->valueMask,
						this->valueList);
	xcb_map_window(Venus::xcb, this->id);
	xcb_change_property(Venus::xcb,
					xcb_prop_mode_t::XCB_PROP_MODE_REPLACE,
					this->id,
					XCB_ATOM_WM_NAME,
					XCB_ATOM_STRING,
					8 * sizeof(char), // --> [8 bits / char]
					strlen(title),
					title);
	xcb_flush(Venus::xcb);
}

void
Window::Poll(void)
{
	xcb_poll_for_event(Venus::xcb);	
}

bool
Window::IsOpened(void)
{
	return (this->isOpened);
}

bool
Window::IsClosed(void)
{
	return (!this->isOpened);
}

WAtom
Window::GetAtom(const char* pAtomName)
{
	xcb_atom_t	ret;
	xcb_intern_atom_cookie_t	cookie;
	xcb_intern_atom_reply_t*	reply;

	cookie = xcb_intern_atom(Venus::xcb, 0, strlen(pAtomName), pAtomName);
	reply = xcb_intern_atom_reply(Venus::xcb, cookie, nullptr);
	ret = reply->atom;
	free(reply);
	return (ret);
}

// @param pFlagWhen: Tous les flags commençant par XCB_EVENT_MASK_...
// @param pAtomAction:
// @param state: true/false
// @param 
void
Window::RecvLocalEvent(int pFlagWhen, WAtom pAtomAction, unsigned int pState, WindowState pWState)
{
	xcb_client_message_event_t	event{};
	event.response_type = XCB_CLIENT_MESSAGE;
	event.window = this->id;
	event.type = pAtomAction;
	event.format = sizeof(pState);
	if (sizeof(pState) == 32U)
		event.data.data32[cast<int>(pWState)] = pState;
	else if (sizeof(pState) == 16U)
		event.data.data16[cast<int>(pWState)] = pState;
	else
		event.data.data8[cast<int>(pWState)] = pState;
	xcb_send_event(Venus::xcb, 0, this->id, pFlagWhen, ptrCast<const char*>(&event));
	xcb_flush(Venus::xcb);
}

void
Window::Close(void)
{
	if (this->isOpened)
	{
		xcb_unmap_window(Venus::xcb, this->id);
		xcb_flush(Venus::xcb);
		this->isOpened = false;
	}
}

void
Window::Open(void)
{
	if (!this->isOpened)
	{
		xcb_map_window(Venus::xcb, this->id);
		xcb_flush(Venus::xcb);
		this->isOpened = true;
	}
}

void
Window::ChangeTitle(const char* title)
{
	this->__ChangeTitle(title, strlen(title));
}

void
Window::ChangeTitle(const char* title, unsigned int size)
{
	this->__ChangeTitle(title, size);
}

unsigned int
Window::GetXcbID(void)
{
	return (this->id);
}

Window::~Window(void)
{
	this->Destroy();
}

void
Window::Destroy(void)
{
	if (!this->isDestroyed)
	{
		xcb_unmap_window(Venus::xcb, this->id);
		xcb_destroy_window(Venus::xcb, this->id);
		this->isDestroyed = true;
	}
}

void
Window::__ChangeTitle(const char* title, unsigned int size)
{
	xcb_change_property(Venus::xcb,
					xcb_prop_mode_t::XCB_PROP_MODE_REPLACE,
					this->id,
					XCB_ATOM_WM_NAME,
					XCB_ATOM_STRING,
					8 * sizeof(char), // --> [8 bits / char]
					size,
					title);
	xcb_flush(Venus::xcb);
}
