/* PETRA DEVELOPPMENT SCRIPT WIZARD */

#ifndef PETRA_DEV_
#define PETRA_DEV_

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
