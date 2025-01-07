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

#ifndef PETRA_HELPER_HPP
#define PETRA_HELPER_HPP

# define SCRIPTS_LOCAL	"./Scripts/"

# define HFW(str, f)			HELPER_FWRITE(str, f)
# define HFW_nl(f)				HELPER_FWRITE_nl(f)
# define HFW_INTRO_NOTE(f)		HELPER_FWRITE_INTRO_NOTE(f)
# define HFW_include(fileN, f)	HELPER_FWRITE_include(fileN, f)
# define HFW_define(f)			HELPER_FWRITE_define(f)
# define HFW_ifndef(f)			HELPER_FWRITE_ifndef(f)
# define HFW_endif(f)			HELPER_FWRITE_endif(f)
# define HFW_class(f)			HELPER_FWRITE_class(f)
# define HFW_struct(f)			HELPER_FWRITE_struct(f)
# define HFW_enum(f)			HELPER_FWRITE_enum(f)
# define HFW_RAW(rawWord, f)	HELPER_FWRITE_RAW(rawWord, f)
# define HFW_brace_o(f)			HELPER_FWRITE_brace_o(f)
# define HFW_brace_c(f)			HELPER_FWRITE_brace_c(f)
# define HFW_comma(f)			HELPER_FWRITE_comma(f)
# define HFW_private(f)			HELPER_FWRITE_private(f)
# define HFW_protected(f)		HELPER_FWRITE_protected(f)
# define HFW_public(f)			HELPER_FWRITE_public(f)
# define HFW_virtual(f)			HELPER_FWRITE_virtual(f)
# define HFW_void(f)			HELPER_FWRITE_void(f)
# define HFW_override(f)		HELPER_FWRITE_override(f)
# define HFW_BeforePulse(f)		HELPER_FWRITE_BeforePulse(f);
# define HFW_Pulse(f)			HELPER_FWRITE_Pulse(f);
# define HFW_AfterPulse(f)		HELPER_FWRITE_AfterPulse(f);

# define HELPER_FWRITE(str, f)			fwrite(str, sizeof(char), str.Size(), f)
# define HELPER_FWRITE_nl(f)			fwrite("\n", sizeof(char), 1, f)
# define HELPER_FWRITE_INTRO_NOTE(f)	fwrite("/* PETRA DEVELOPPMENT SCRIPT WIZARD */\n\n", sizeof(char), 40, f)
# define HELPER_FWRITE_include(file, f)	fwrite("#include ", sizeof(char), 9, f); fwrite(#file, sizeof(char), String::size(#file), f);
# define HELPER_FWRITE_define(f)		fwrite("#define ", sizeof(char), 8, f)
# define HELPER_FWRITE_ifndef(f)		fwrite("#ifndef ", sizeof(char), 8, f)
# define HELPER_FWRITE_endif(f)			fwrite("#endif\n", sizeof(char), 7, f)
# define HELPER_FWRITE_class(f)			fwrite("class ", sizeof(char), 6, f)
# define HELPER_FWRITE_struct(f)		fwrite("struct ", sizeof(char), 7, f)
# define HELPER_FWRITE_enum(f)			fwrite("enum ", sizeof(char), 5, f)
# define HELPER_FWRITE_RAW(rawWord, f)	fwrite(#rawWord, sizeof(char), String::size(#rawWord), f)//String::Size(#rawWord), f)
# define HELPER_FWRITE_brace_o(f)		fwrite("{", sizeof(char), 1, f)
# define HELPER_FWRITE_brace_c(f)		fwrite("}", sizeof(char), 1, f)
# define HELPER_FWRITE_comma(f)			fwrite(";\n", sizeof(char), 2, f)
# define HELPER_FWRITE_private(f)		fwrite("pivate:\n", sizeof(char), 8, f)
# define HELPER_FWRITE_public(f)		fwrite("public:\n", sizeof(char), 8, f)
# define HELPER_FWRITE_protected(f)		fwrite("protected:\n", sizeof(char), 11, f)
# define HELPER_FWRITE_virtual(f)		fwrite("virtual ", sizeof(char), 8, f)
# define HELPER_FWRITE_void(f)			fwrite("void \n", sizeof(char), 6, f)
# define HELPER_FWRITE_override(f)		fwrite("override", sizeof(char), 9, f)
# define HELPER_FWRITE_BeforePulse(f)	fwrite("\tvirtual void\n\tBeforePulse(void) override;\n\n", sizeof(char), 44, f)
# define HELPER_FWRITE_Pulse(f)			fwrite("\tvirtual void\n\tPulse(float deltaTime) override;\n\n", sizeof(char), 49, f)
# define HELPER_FWRITE_AfterPulse(f)	fwrite("\tvirtual void\n\tAfterPulse(void) override;\n\n", sizeof(char), 43, f)
# define HELPER_FWRITE_PREFIX(pre, f)	fwrite(#pre, sizeof(char), String::size(#pre), f); fwrite("::", sizeof(char), 2, f)

# define WIZARD_SCRIPT(classT)	\
	Helper::CreateScriptTemplate(classT);

# include "../Egide/egide/egide.h"

class Helper final
{
public:
	static void
	CreateScriptTemplate(String&& className);

private:
	static void
	__CreateCPPScriptTemplate(const String& className);

		static void
	__CreateHPPScriptTemplate(const String& className);
};

#endif
