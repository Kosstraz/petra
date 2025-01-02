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

#include "Window.hpp"

Window::Window(const String& name, int w, int h)
{
	this->glfwPtr = glfwCreateWindow(w, h, name.Data(), nullptr, nullptr);
	if (!this->glfwPtr)
		throw (Window::WindowCouldNotBeCreated());
	this->width = w;
	this->heigth = h;
	this->title = name;
	this->destroyed = false;
}

Window::~Window(void)
{
	this->Destroy();
}

void
Window::Destroy(void)
{
	if (!this->destroyed)
	{
		this->Close();
		glfwDestroyWindow(this->glfwPtr);
		this->destroyed = true;
	}
}
