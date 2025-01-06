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

#include "Helper.hpp"
#include <string>
#include <cstdlib>
#include <fcntl.h>

std::string
CapitalizeString(std::string str)
{
	for (unsigned int i = 0 ; i < str.size() ; ++i)
		if (str[i] >= 97 && str[i] <= 122)
			str[i] -= 32;
	return (str);
}

void
Helper::CreateScriptTemplate(std::string&& className)
{
	Helper::__CreateHPPScriptTemplate(className);
	Helper::__CreateCPPScriptTemplate(className);
}

void
Helper::__CreateCPPScriptTemplate(const std::string& className)
{
	std::string	fileName	=  std::string(SCRIPTS_LOCAL) + std::string(className) + ".cpp";
	FILE*		file		= fopen(fileName.c_str(), "w");
	if (!file)
	{
		std::cout << "Impossible de créer " << className << ".cpp :/\n";
		return ;
	}

	HFW_INTRO_NOTE(file);

	HFW(std::string("#include \""), file);
	HFW(std::string(className + ".hpp"), file);
	HFW(std::string("\"\n"), file);
	HFW_nl(file);

	HFW(std::string("void\n"), file);
	HFW(className, file);
	HFW(std::string("::"), file);
	HFW(std::string("BeforePulse(void)\n{\n}\n\n"), file);

	HFW(std::string("void\n"), file);
	HFW(className, file);
	HFW(std::string("::"), file);
	HFW(std::string("Pulse(float deltaTime)\n{\n}\n\n"),  file);

	HFW(std::string("void\n"), file);
	HFW(className, file);
	HFW(std::string("::"), file);
	HFW(std::string("AfterPulse(void)\n{\n}\n\n"), file);

	fclose(file);
}

void
Helper::__CreateHPPScriptTemplate(const std::string& className)
{
	std::string	fileName	=  std::string(SCRIPTS_LOCAL) + std::string(className) + ".hpp";
	FILE*		file		= fopen(fileName.c_str(), "w");
	if (!file)
	{
		std::cout << "Impossible de créer " << className << ".hpp :/\n";
		return ;
	}
	std::string		headerProtect("PETRA_DEV_");

	HFW_INTRO_NOTE(file);

	HFW_ifndef(file);
	HFW(headerProtect, file);
	HFW_nl(file);
	HFW_define(file);
	HFW(headerProtect, file);
	HFW_nl(file);

	HFW(std::string("\n# include \"egide.h\"\n\n"), file);

	HFW(std::string("GESTALT_USE\n"), file);
	HFW_class(file);
	HFW(className, file);
	HFW(std::string(" : Gestalt"), file);
	HFW_nl(file);
	HFW_brace_o(file);
	HFW_nl(file);
	HFW_public(file);

	HFW_BeforePulse(file);
	HFW_Pulse(file);
	HFW_AfterPulse(file);

	HFW_brace_c(file);
	HFW_comma(file);
	HFW(std::string("GESTALT_ACTIVE("), file);
	HFW(className, file);
	HFW(std::string(")\n"), file);
	HFW_nl(file);
	HFW_endif(file);
	fclose(file);
}
