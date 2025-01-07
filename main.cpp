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

#include "petra.h"
#include <thread>

int	a(void)
{
	std::cout << 42.42f << std::endl;
	return (0);
}

int	b(int a, int b, float c, double d)
{
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	return (0);
}

class A
{
public:
	A(const char* pA) : norage(pA)
	{}

	void
	Hihi(void)
	{
		std::cout << this->norage << std::endl;
	}

	void
	Ahah(int a, int b, float c, double d)
	{
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		std::cout << d << std::endl;
		std::cout << this->norage << std::endl;
	}

private:
	const char* norage;
};

int	main(void)
{
	//WIZARD_SCRIPT("Player");
	//Petra::Init();
	//Petra::Loop();
	//Petra::Destroy();
	//Gestalt::DestroyObjects();
	return (0);
}
