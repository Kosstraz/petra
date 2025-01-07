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

String
CapitalizeString(String str)
{
	for (unsigned int i = 0 ; i < str.Size() ; ++i)
		if (str[i] >= 97 && str[i] <= 122)
			str[i] -= 32;
	return (str);
}

void
Helper::CreateScriptTemplate(String&& className)
{
	Helper::__CreateHPPScriptTemplate(className);
	Helper::__CreateCPPScriptTemplate(className);
}

void
Helper::__CreateCPPScriptTemplate(const String& className)
{
	String	fileName	=  SCRIPTS_LOCAL + className + ".cpp";
	FILE*		file	= fopen(fileName, "w");
	if (!file)
	{
		std::cout << "Impossible de créer " << className << ".cpp :/\n";
		return ;
	}

	HFW_INTRO_NOTE(file);

	HFW(String("#include \""), file);
	HFW(String(className + ".hpp"), file);
	HFW(String("\"\n"), file);
	HFW_nl(file);

	HFW(String("void\n"), file);
	HFW(className, file);
	HFW(String("::"), file);
	HFW(String("BeforePulse(void)\n{\n}\n\n"), file);

	HFW(String("void\n"), file);
	HFW(className, file);
	HFW(String("::"), file);
	HFW(String("Pulse(float deltaTime)\n{\n}\n\n"),  file);

	HFW(String("void\n"), file);
	HFW(className, file);
	HFW(String("::"), file);
	HFW(String("AfterPulse(void)\n{\n}\n\n"), file);

	fclose(file);
}

void
Helper::__CreateHPPScriptTemplate(const String& className)
{
	String	fileName	= SCRIPTS_LOCAL + className + ".hpp";
	FILE*		file	= fopen(fileName, "w");
	if (!file)
	{
		std::cout << "Impossible de créer " << className << ".hpp :/\n";
		return ;
	}
	String		headerProtect("PETRA_DEV_");

	HFW_INTRO_NOTE(file);

	HFW_ifndef(file);
	HFW(headerProtect, file);
	HFW_nl(file);
	HFW_define(file);
	HFW(headerProtect, file);
	HFW_nl(file);

	HFW(String("\n# include \"egide.h\"\n\n"), file);

	HFW(String("GESTALT_USE\n"), file);
	HFW_class(file);
	HFW(className, file);
	HFW(String(" : Gestalt"), file);
	HFW_nl(file);
	HFW_brace_o(file);
	HFW_nl(file);
	HFW_public(file);

	HFW_BeforePulse(file);
	HFW_Pulse(file);
	HFW_AfterPulse(file);

	HFW_brace_c(file);
	HFW_comma(file);
	HFW(String("GESTALT_ACTIVE("), file);
	HFW(className, file);
	HFW(String(")\n"), file);
	HFW_nl(file);
	HFW_endif(file);
	fclose(file);
}
