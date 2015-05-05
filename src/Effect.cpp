#include "Effect.h"



Effect::~Effect()
{
}


void Buff::UpdateAndApply(float dt, float* stat)
{

	*stat += modifier_;

	if (timeleft_ >= 0)
		timeleft_ -= dt;

	if (duration_ - timeleft_ >= 1)
		duration_ -= 1;
}



void Debuff::UpdateAndApply(float dt, float* stat)
{

	if (float(duration_)-timeleft_ >= 1.0) { // tick effect
		duration_ -= 1;
		*stat -= modifier_;
	}

	if (timeleft_ >= 0)
		timeleft_ -= dt;
}
