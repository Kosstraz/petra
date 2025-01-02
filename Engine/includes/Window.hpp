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

#ifndef PETRA_WINDOW_HPP
#define PETRA_WINDOW_HPP

#include <nsl.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(void)			= delete;
	Window(const Window&)	= delete;
	Window(Window&&)		= delete;
	Window(const String& title, int width, int height);
	~Window(void);

	FORCEINLINE
	void
	Close(void)
	{
		glfwSetWindowShouldClose(this->glfwPtr, true);
	}

	FORCEINLINE
	bool
	IsClosed(void)
	{
		return (glfwWindowShouldClose(this->glfwPtr));
	}

	FORCEINLINE
	bool
	IsOpened(void)
	{
		return (!glfwWindowShouldClose(this->glfwPtr));
	}

	FORCEINLINE
	operator GLFWwindow*(void)
	{
		return (this->glfwPtr);
	}

	void
	Destroy(void);

private:
	GLFWwindow*	glfwPtr;
	String		title;
	int			width;
	int			heigth;
	bool		destroyed;

public:
	struct WindowCouldNotBeCreated : std::exception { virtual const char* what(void) const noexcept override { return ("The window could'nt be created !\n"); } };
};

#endif
