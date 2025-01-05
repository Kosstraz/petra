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
#include <cstring>

Window::Window(const char* title, int width, int height) :
	isDestroyed(false),
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
