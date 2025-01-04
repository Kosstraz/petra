/* PETRA DEVELOPPMENT SCRIPT WIZARD */

#ifndef PETRA_DEV_HPP
#define PETRA_DEV_HPP

# include "petra.h"

GESTALT_USE
class AutoGenerationScript : Gestalt
{
public:
	virtual void
	BeforePulse(void) override;

	virtual void
	Pulse(float deltaTime) override;

	virtual void
	AfterPulse(void) override;

};
GESTALT_ACTIVE(AutoGenerationScript)

#endif
