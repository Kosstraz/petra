/* PETRA DEVELOPPMENT SCRIPT WIZARD */

#include "AutoGenerationScript.hpp"

void
AutoGenerationScript::BeforePulse(void)
{
	std::cout << "BeforePulse\n";
}

void
AutoGenerationScript::Pulse(float deltaTime)
{
	std::cout << "Pulse " << deltaTime << "\n";
}

void
AutoGenerationScript::AfterPulse(void)
{
	std::cout << "AfterPulse\n";
}

